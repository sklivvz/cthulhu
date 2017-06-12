#include "redismodule.h"
#include "duktape.h"
#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

duk_context *_ctx;
RedisModuleCtx *RM_ctx;

int CthulhuInvoke_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {

  size_t length;

  RM_ctx = ctx;

  if (argc < 2) {
    return RedisModule_WrongArity(ctx);
  }

  duk_push_global_object(_ctx);
  duk_get_prop_string(_ctx, -1, RedisModule_StringPtrLen(argv[1], &length));

  for (int i = 2; i < argc; i++) {
    duk_push_string(_ctx, RedisModule_StringPtrLen(argv[i], &length));
  }

  if (duk_pcall(_ctx, argc - 2) != DUK_EXEC_SUCCESS) {
    const char * error = duk_safe_to_string(_ctx, -1);
    duk_pop(_ctx);
    return RedisModule_ReplyWithSimpleString(ctx, error);
  }
  
  const char * result = duk_to_string(_ctx, -1);
  duk_pop(_ctx);

  if (result == NULL) {
    return RedisModule_ReplyWithNull(ctx);
  }

  return RedisModule_ReplyWithSimpleString(ctx, result);
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  
  RM_ctx = ctx;
  
  if (RedisModule_Init(ctx,"cthulhu",1,REDISMODULE_APIVER_1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  if (argc != 1) {
    return REDISMODULE_ERR;
  }

  size_t len = 0;
  const char * filename = RedisModule_StringPtrLen(argv[0], &len);
  
  //TODO: see http://duktape.org/guide.html#error-handling
  _ctx = duk_create_heap_default();
  if (!_ctx) {
    printf("Failed to create a Duktape heap.\n");
    return REDISMODULE_ERR;
  }

  register_commands(_ctx);

  if (load_file_to_context(_ctx, filename)<0) return REDISMODULE_ERR;

  if (duk_peval(_ctx) != 0) {
    printf("Compile failed: %s\n", duk_safe_to_string(_ctx, -1));
    return REDISMODULE_ERR;
  }

  duk_pop(_ctx);

  if (RedisModule_CreateCommand(ctx, "invoke", CthulhuInvoke_RedisCommand, "write", 0, -1, 1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  return REDISMODULE_OK;
}

void RedisModule_OnUnload() {
  duk_destroy_heap(_ctx);
}
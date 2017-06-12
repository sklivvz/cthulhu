#include "redismodule.h"
#include "duktape.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

duk_context *_ctx;
RedisModuleCtx *RM_ctx;

duk_ret_t lpush(duk_context *_ctx) {

  const char * key = duk_require_string(_ctx, 0); // key name
  duk_bool_t where = duk_require_boolean(_ctx, 1); // true: head, false: tail
  const char * value = duk_require_string(_ctx, 2); // value

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  
  RedisModule_ListPush(
    key_h, 
    (where ? REDISMODULE_LIST_HEAD : REDISMODULE_LIST_TAIL),
    RMS_Value
  );

  printf("\nlpush called with %s, %s, %d\n", key, value, where);

  RedisModule_CloseKey(key_h);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  return 0;
}

int load_file_to_context(const char *filename) 
{ 
	size_t size = 0;
	FILE *f = fopen(filename, "rb");
  char * source;

	if (f == NULL) 
	{ 
    source = NULL;
    duk_push_undefined(_ctx);
		return -1;
	} 
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	source = (char *)RedisModule_Alloc(size);
	if (size != fread(source, sizeof(char), size, f)) 
	{ 
		RedisModule_Free(source);
    source = NULL;
    duk_push_undefined(_ctx);
		return -2;
	} 
	fclose(f);
	duk_push_lstring(_ctx, (const char *) source, (duk_size_t) size);
	return size;
}


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

  duk_push_global_object(_ctx);
  duk_push_c_function(_ctx, lpush, 3);
  duk_put_prop_string(_ctx, -2, "redisLPush");

  if (load_file_to_context(filename)<0) return REDISMODULE_ERR;

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
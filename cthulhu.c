#include "redismodule.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "duktape.h"

/*static duk_ret_t js_export(duk_context *ctx) {
  int n = duk_get_top(ctx);  // #args 
  printf("argc %d", n);
  for (int i = 0; i < n; i++) {
    printf("arg %d: %s\n",i,duk_to_string(ctx, i));
  }
  return 1;  // one return value 
}*/

duk_context *_ctx;

int load_file_to_memory(const char *filename, char ** source_ref) 
{ 
	size_t size = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL) 
	{ 
    *source_ref = NULL;
		return -1;
	} 
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	*source_ref = (char *)RedisModule_Alloc(size+1);
	if (size != fread(*source_ref, sizeof(char), size, f)) 
	{ 
		RedisModule_Free(*source_ref);
    *source_ref = NULL;
		return -2;
	} 
	fclose(f);
	(*source_ref)[size] = 0;
	return size;
}


int CthulhuInvoke_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (argc < 1) {
    return RedisModule_WrongArity(ctx);
  }

  duk_dup(_ctx,-1);

  size_t length;

  for (int i = 1; i < argc; i++) {
    duk_push_string(_ctx, RedisModule_StringPtrLen(argv[i], &length));
  }

  if (duk_pcall(_ctx, argc - 1) != DUK_EXEC_SUCCESS) {
    const char * error = duk_safe_to_string(_ctx, -1);
    duk_pop(_ctx);
    return RedisModule_ReplyWithSimpleString(ctx, error);
  }
  
  const char * result = duk_get_string(_ctx, -1);

  duk_pop(_ctx);

  if (result == NULL) {
    return RedisModule_ReplyWithNull(ctx);
  }

  return RedisModule_ReplyWithSimpleString(ctx, result);
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  int step = 0;
  
  if (RedisModule_Init(ctx,"cthulhu",1,REDISMODULE_APIVER_1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  if (argc != 1) {
    return REDISMODULE_ERR;
  }

  size_t len = 0;
  const char * filename = RedisModule_StringPtrLen(argv[0], &len);
  
  char * source;
 
  if (load_file_to_memory(filename, &source)<0) return REDISMODULE_ERR;

  _ctx = duk_create_heap_default();
 
  if (duk_pcompile_string(_ctx, 0, source) != 0) {
    printf("compile failed: %s\n", duk_safe_to_string(_ctx, -1));
    return REDISMODULE_ERR;
  }

  if (RedisModule_CreateCommand(ctx, "invoke", CthulhuInvoke_RedisCommand, "write", 0, -1, 1) == REDISMODULE_ERR) {
      return REDISMODULE_ERR;
  }

  return REDISMODULE_OK;
}

void RedisModule_OnUnload() {
  duk_destroy_heap(_ctx);
}
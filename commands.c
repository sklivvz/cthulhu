#include "commands.h"

//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <errno.h>
//#include <string.h>

void register_commands(duk_context *_ctx) {
  duk_push_global_object(_ctx);
 
  duk_push_c_function(_ctx, list_push, 3);
  duk_put_prop_string(_ctx, -2, "redisListPush");


}


duk_ret_t list_push(duk_context *_ctx) {

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

  RedisModule_CloseKey(key_h);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  return 0;
}



int load_file_to_context(duk_context *_ctx, const char *filename) { 
	size_t size = 0;
	FILE *f = fopen(filename, "rb");
  char * source;

	if (f == NULL) 	{ 
    source = NULL;
    duk_push_undefined(_ctx);
		return -1;
	} 
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	source = (char *)RedisModule_Alloc(size);
	if (size != fread(source, sizeof(char), size, f)) { 
		RedisModule_Free(source);
    source = NULL;
    duk_push_undefined(_ctx);
		return -2;
	} 
	fclose(f);
	duk_push_lstring(_ctx, (const char *) source, (duk_size_t) size);
	return size;
}
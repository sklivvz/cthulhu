#include "commands.h"

//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <errno.h>
//#include <string.h>

void register_commands(duk_context *_ctx) {
  duk_push_global_object(_ctx);
  duk_idx_t idx_top = duk_get_top_index(_ctx);
 
  duk_push_c_function(_ctx, milliseconds, 0);
  duk_put_prop_string(_ctx, idx_top, "redisMilliseconds");

  duk_push_c_function(_ctx, get_client_id, 0);
  duk_put_prop_string(_ctx, idx_top, "redisGetClientId");

  duk_push_c_function(_ctx, get_selected_db, 0);
  duk_put_prop_string(_ctx, idx_top, "redisGetSelectedDb");

  duk_push_c_function(_ctx, select_db, 1);
  duk_put_prop_string(_ctx, idx_top, "redisSelectDb");

  duk_push_c_function(_ctx, length, 1);
  duk_put_prop_string(_ctx, idx_top, "redisLength");

  duk_push_c_function(_ctx, delete_key, 1);
  duk_put_prop_string(_ctx, idx_top, "redisDeleteKey");

  duk_push_c_function(_ctx, list_push, 3);
  duk_put_prop_string(_ctx, idx_top, "redisListPush");
  
  duk_push_c_function(_ctx, list_pop, 2);
  duk_put_prop_string(_ctx, idx_top, "redisListPop");

  duk_push_c_function(_ctx, log_to_redis, 2);
  duk_put_prop_string(_ctx, idx_top, "redisLog");
}

duk_ret_t milliseconds(duk_context *_ctx){
  duk_push_number(_ctx, RedisModule_Milliseconds());
  return 1;
}

duk_ret_t get_client_id(duk_context *_ctx){
  duk_push_number(_ctx, RedisModule_GetClientId(RM_ctx));
  return 1;
}

duk_ret_t get_selected_db(duk_context *_ctx){
  duk_push_number(_ctx, RedisModule_GetSelectedDb(RM_ctx));
  return 1;
}

duk_ret_t select_db(duk_context *_ctx){
  int newid = duk_require_int(_ctx, 0);
  RedisModule_SelectDb(RM_ctx, newid);
  return 0;
}

duk_ret_t length(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  size_t ret = RedisModule_ValueLength(key_h);
  RedisModule_CloseKey(key_h);
  duk_push_number(_ctx, ret);
  RedisModule_FreeString(RM_ctx, RMS_Key);
  return 1;
}

duk_ret_t delete_key(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  RedisModule_DeleteKey(key_h);
  RedisModule_CloseKey(key_h);
  RedisModule_FreeString(RM_ctx, RMS_Key);
  return 0;
}

duk_ret_t get_expire(duk_context *_ctx){

}

duk_ret_t set_expire(duk_context *_ctx){

}

duk_ret_t string_set(duk_context *_ctx){

}

duk_ret_t string_truncate(duk_context *_ctx){

}


duk_ret_t list_push(duk_context *_ctx) {

  const char * key = duk_require_string(_ctx, 0); // key name
  duk_bool_t where = duk_require_boolean(_ctx, 1); // true: head, false: tail
  const char * value = duk_to_string(_ctx, 2); // value

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  
  RedisModule_ListPush(
    key_h, 
    (where ? REDISMODULE_LIST_HEAD : REDISMODULE_LIST_TAIL),
    RMS_Value
  );

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  return 0;
}

duk_ret_t list_pop(duk_context *_ctx) {
  size_t len;

  const char * key = duk_require_string(_ctx, 0); // key name
  duk_bool_t where = duk_require_boolean(_ctx, 1); // true: head, false: tail

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  
  RedisModuleString *RMS_Value = RedisModule_ListPop(
    key_h, 
    (where ? REDISMODULE_LIST_HEAD : REDISMODULE_LIST_TAIL)
  );

  RedisModule_CloseKey(key_h);

  duk_push_string(_ctx, RedisModule_StringPtrLen(RMS_Value, &len));

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  return 1;
}

duk_ret_t log_to_redis(duk_context *_ctx){
  const char * level = duk_to_string(_ctx, 0);
  const char * message = duk_to_string(_ctx, 1);
  RedisModule_Log(RM_ctx, level, message);
  duk_pop(_ctx);
  duk_pop(_ctx);
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
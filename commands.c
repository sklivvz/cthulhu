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

  duk_push_c_function(_ctx, get_expire, 1);
  duk_put_prop_string(_ctx, idx_top, "redisGetExpire");

  duk_push_c_function(_ctx, set_expire, 2);
  duk_put_prop_string(_ctx, idx_top, "redisSetExpire");

  duk_push_c_function(_ctx, string_set, 2);
  duk_put_prop_string(_ctx, idx_top, "redisStringSet");

  duk_push_c_function(_ctx, string_truncate, 2);
  duk_put_prop_string(_ctx, idx_top, "redisStringTruncate");

  duk_push_c_function(_ctx, string_get, 1);
  duk_put_prop_string(_ctx, idx_top, "redisStringGet");

  duk_push_c_function(_ctx, list_push, 3);
  duk_put_prop_string(_ctx, idx_top, "redisListPush");
  
  duk_push_c_function(_ctx, list_pop, 2);
  duk_put_prop_string(_ctx, idx_top, "redisListPop");

  duk_push_c_function(_ctx, hash_set, 3);
  duk_put_prop_string(_ctx, idx_top, "redisHashSet");

  duk_push_c_function(_ctx, hash_set_if_present, 3);
  duk_put_prop_string(_ctx, idx_top, "redisHashSetIfPresent");

  duk_push_c_function(_ctx, hash_set_if_absent, 3);
  duk_put_prop_string(_ctx, idx_top, "redisHashSetIfAbsent");

  duk_push_c_function(_ctx, hash_unset, 2);
  duk_put_prop_string(_ctx, idx_top, "redisHashUnset");

  duk_push_c_function(_ctx, hash_is_set, 2);
  duk_put_prop_string(_ctx, idx_top, "redisHashIsSet");

  duk_push_c_function(_ctx, hash_get, 2);
  duk_put_prop_string(_ctx, idx_top, "redisHashGet");

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
  int ret = RedisModule_SelectDb(RM_ctx, newid);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t length(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
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
  int ret = RedisModule_DeleteKey(key_h);
  RedisModule_CloseKey(key_h);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t get_expire(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
  mstime_t ret = RedisModule_GetExpire(key_h);
  RedisModule_CloseKey(key_h);
  duk_push_number(_ctx, ret);
  RedisModule_FreeString(RM_ctx, RMS_Key);
  return 1;
}

duk_ret_t set_expire(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  mstime_t expire = duk_require_int(_ctx, 1);
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_SetExpire(key_h, expire);
  RedisModule_CloseKey(key_h);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t string_set(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * value = duk_to_string(_ctx, 1); // value
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_StringSet(key_h, RMS_Value);
  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);
  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t string_truncate(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  mstime_t newlen = duk_require_int(_ctx, 1);
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_StringTruncate(key_h, newlen);
  RedisModule_CloseKey(key_h);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t string_get(duk_context *ctx) {
  size_t len;
  const char * key = duk_require_string(_ctx, 0); // key name
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
  char *result = RedisModule_StringDMA(key_h, &len, REDISMODULE_READ);
  RedisModule_CloseKey(key_h);
  duk_push_string(_ctx, result);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  return 1;
}


duk_ret_t list_push(duk_context *_ctx) {
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_bool_t where = duk_require_boolean(_ctx, 1); // true: head, false: tail
  const char * value = duk_to_string(_ctx, 2); // value

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  
  int ret = RedisModule_ListPush(key_h, (where ? REDISMODULE_LIST_HEAD : REDISMODULE_LIST_TAIL), RMS_Value);

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t list_pop(duk_context *_ctx) {

  const char * key = duk_require_string(_ctx, 0); // key name
  duk_bool_t where = duk_require_boolean(_ctx, 1); // true: head, false: tail

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  
  RedisModuleString *RMS_Value = RedisModule_ListPop(key_h, (where ? REDISMODULE_LIST_HEAD : REDISMODULE_LIST_TAIL));

  RedisModule_CloseKey(key_h);

  size_t len;
  duk_push_string(_ctx, RedisModule_StringPtrLen(RMS_Value, &len));

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  return 1;
}

duk_ret_t hash_set(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  const char * hashvalue = duk_to_string(_ctx, 2); // hash value
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_HashValue = RedisModule_CreateString(RM_ctx, hashvalue, strlen(hashvalue));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);

  int ret = RedisModule_HashSet(key_h, REDISMODULE_HASH_NONE | REDISMODULE_HASH_CFIELDS, hashkey, RMS_HashValue, NULL);

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);
  duk_pop(_ctx);
  RedisModule_FreeString(RM_ctx, RMS_HashValue);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t hash_set_if_absent(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  const char * hashvalue = duk_to_string(_ctx, 2); // hash value
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_HashValue = RedisModule_CreateString(RM_ctx, hashvalue, strlen(hashvalue));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);

  int ret = RedisModule_HashSet(key_h, REDISMODULE_HASH_NX | REDISMODULE_HASH_CFIELDS, hashkey, RMS_HashValue, NULL);

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);
  duk_pop(_ctx);
  RedisModule_FreeString(RM_ctx, RMS_HashValue);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t hash_set_if_present(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  const char * hashvalue = duk_to_string(_ctx, 2); // hash value
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_HashValue = RedisModule_CreateString(RM_ctx, hashvalue, strlen(hashvalue));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);

  int ret = RedisModule_HashSet(key_h, REDISMODULE_HASH_XX | REDISMODULE_HASH_CFIELDS, hashkey, RMS_HashValue, NULL);

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);
  duk_pop(_ctx);
  RedisModule_FreeString(RM_ctx, RMS_HashValue);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t hash_unset(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);

  int ret = RedisModule_HashSet(key_h, REDISMODULE_HASH_CFIELDS, hashkey, REDISMODULE_HASH_DELETE, NULL);

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK ? 1 : 0);
  return 1;
}

duk_ret_t hash_is_set(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  int exists;
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
printf("hash %s\n", key);
printf("key %s\n", hashkey);

  int ret = RedisModule_HashGet(key_h, REDISMODULE_HASH_CFIELDS | REDISMODULE_HASH_EXISTS, hashkey, &exists, NULL);

printf("exists %d - ret %d", exists, ret);

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);

  size_t len;

  duk_push_boolean(_ctx, exists);
  return 1;
}

duk_ret_t hash_get(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_HashValue;
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);

  int ret = RedisModule_HashGet(key_h, REDISMODULE_HASH_CFIELDS, hashkey, &RMS_HashValue, NULL);

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);

  size_t len;
  duk_push_string(_ctx, RedisModule_StringPtrLen(RMS_HashValue, &len));

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_HashValue);

  return 1;
}

duk_ret_t log_to_redis(duk_context *_ctx){
  const char * level = duk_to_string(_ctx, 0);
  const char * message = duk_to_string(_ctx, 1);
  RedisModule_Log(RM_ctx, level, message);
  duk_pop(_ctx);
  duk_pop(_ctx);

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
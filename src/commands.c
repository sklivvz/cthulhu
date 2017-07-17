
// Copyright 2017 Marco Cecconi
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "commands.h"


void register_commands(duk_context *_ctx) {
  auto_replication = 1;

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

  duk_push_c_function(_ctx, string_get, 1);
  duk_put_prop_string(_ctx, idx_top, "redisStringGet");

  duk_push_c_function(_ctx, list_push, 3);
  duk_put_prop_string(_ctx, idx_top, "redisListPush");
  
  duk_push_c_function(_ctx, list_pop, 2);
  duk_put_prop_string(_ctx, idx_top, "redisListPop");

  duk_push_c_function(_ctx, zset_add, 3);
  duk_put_prop_string(_ctx, idx_top, "redisZsetAdd");

  duk_push_c_function(_ctx, zset_update_if_present, 3);
  duk_put_prop_string(_ctx, idx_top, "redisZsetUpdateIfPresent");

  duk_push_c_function(_ctx, zset_add_if_absent, 3);
  duk_put_prop_string(_ctx, idx_top, "redisZsetAddIfAbsent");

  duk_push_c_function(_ctx, zset_incrby, 3);
  duk_put_prop_string(_ctx, idx_top, "redisZsetIncrby");

  duk_push_c_function(_ctx, zset_incrby_if_present, 3);
  duk_put_prop_string(_ctx, idx_top, "redisZsetIncrbyIfPresent");

  duk_push_c_function(_ctx, zset_incrby_if_absent, 3);
  duk_put_prop_string(_ctx, idx_top, "redisZsetIncrbyIfAbsent");
  
  duk_push_c_function(_ctx, zset_rem, 2);
  duk_put_prop_string(_ctx, idx_top, "redisZsetRem");

  duk_push_c_function(_ctx, zset_score, 2);
  duk_put_prop_string(_ctx, idx_top, "redisZsetScore");

  duk_push_c_function(_ctx, zset_range_stop, 1);
  duk_put_prop_string(_ctx, idx_top, "redisZsetRangeStop");

  duk_push_c_function(_ctx, zset_range_end_reached, 1);
  duk_put_prop_string(_ctx, idx_top, "redisZsetRangeEndReached");

  duk_push_c_function(_ctx, zset_first_in_score_range, 5);
  duk_put_prop_string(_ctx, idx_top, "redisZsetFirstInScoreRange");

  duk_push_c_function(_ctx, zset_last_in_score_range, 5);
  duk_put_prop_string(_ctx, idx_top, "redisZsetLastInScoreRange");

  duk_push_c_function(_ctx, zset_first_in_lex_range, 3);
  duk_put_prop_string(_ctx, idx_top, "redisZsetFirstInLexRange");

  duk_push_c_function(_ctx, zset_last_in_lex_range, 3);
  duk_put_prop_string(_ctx, idx_top, "redisZsetLastInLexRange");

  duk_push_c_function(_ctx, zset_range_current_element, 1);
  duk_put_prop_string(_ctx, idx_top, "redisZsetRangeCurrentElement");

  duk_push_c_function(_ctx, zset_range_next, 1);
  duk_put_prop_string(_ctx, idx_top, "redisZsetRangeNext");

  duk_push_c_function(_ctx, zset_range_prev, 1);
  duk_put_prop_string(_ctx, idx_top, "redisZsetRangePrev");

  duk_push_c_function(_ctx, hash_set, 3);
  duk_put_prop_string(_ctx, idx_top, "redisHashSet");

  duk_push_c_function(_ctx, hash_update_if_present, 3);
  duk_put_prop_string(_ctx, idx_top, "redisHashUpdateIfPresent");

  duk_push_c_function(_ctx, hash_set_if_absent, 3);
  duk_put_prop_string(_ctx, idx_top, "redisHashSetIfAbsent");

  duk_push_c_function(_ctx, hash_unset, 2);
  duk_put_prop_string(_ctx, idx_top, "redisHashUnset");

  duk_push_c_function(_ctx, hash_is_set, 2);
  duk_put_prop_string(_ctx, idx_top, "redisHashIsSet");

  duk_push_c_function(_ctx, hash_get, 2);
  duk_put_prop_string(_ctx, idx_top, "redisHashGet");

  duk_push_c_function(_ctx, set_auto_replication, 1);
  duk_put_prop_string(_ctx, idx_top, "redisSetAutoReplication");

  duk_push_c_function(_ctx, get_auto_replication, 0);
  duk_put_prop_string(_ctx, idx_top, "redisGetAutoReplication");

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

  if (auto_replication)
    RedisModule_Replicate(RM_ctx, "SELECT", "l", newid);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
  return 1;
}

duk_ret_t length(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
  if (key_h == NULL) {
    duk_push_undefined(_ctx);
    RedisModule_FreeString(RM_ctx, RMS_Key);
    return 1;
  } 
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

  if (auto_replication)
    RedisModule_Replicate(RM_ctx, "DEL", "s", RMS_Key);

  RedisModule_CloseKey(key_h);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
  return 1;
}

duk_ret_t get_expire(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
  if (key_h == NULL) {
    duk_push_undefined(_ctx);
    RedisModule_FreeString(RM_ctx, RMS_Key);
    return 1;
  } 

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

  if (auto_replication)
    RedisModule_Replicate(RM_ctx, "EXPIRE", "sl", RMS_Key, expire);

  RedisModule_CloseKey(key_h);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
  return 1;
}

duk_ret_t string_set(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * value = duk_to_string(_ctx, 1); // value
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_StringSet(key_h, RMS_Value);

  if (auto_replication)
    RedisModule_Replicate(RM_ctx, "SET", "ss", RMS_Key, RMS_Value);

  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);
  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
  return 1;
}

duk_ret_t string_get(duk_context *ctx) {
  size_t len;
  const char * key = duk_require_string(_ctx, 0); // key name
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
  if (key_h == NULL) {
    duk_push_undefined(_ctx);
    RedisModule_FreeString(RM_ctx, RMS_Key);
    return 1;
  } 

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

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
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

duk_ret_t zset_add(duk_context *_ctx) {
  int flags;
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_double_t score = duk_require_number(_ctx, 1); // score
  const char * value = duk_to_string(_ctx, 2); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetAdd(key_h, score, RMS_Value, &flags);
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
  return 1;
}

duk_ret_t zset_update_if_present(duk_context *_ctx) {
  int flags = REDISMODULE_ZADD_XX;
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_double_t score = duk_require_number(_ctx, 1); // score
  const char * value = duk_to_string(_ctx, 2); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetAdd(key_h, score, RMS_Value, &flags);
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  duk_push_boolean(_ctx, (ret == REDISMODULE_OK && flags != REDISMODULE_ZADD_NOP));
  return 1;
}

duk_ret_t zset_add_if_absent(duk_context *_ctx) {
  int flags = REDISMODULE_ZADD_NX;
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_double_t score = duk_require_number(_ctx, 1); // score
  const char * value = duk_to_string(_ctx, 2); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetAdd(key_h, score, RMS_Value, &flags);
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  duk_push_boolean(_ctx, (ret == REDISMODULE_OK && flags != REDISMODULE_ZADD_NOP));
  return 1;
}

duk_ret_t zset_incrby(duk_context *_ctx) {
  int flags;
  double newScore;
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_double_t score = duk_require_number(_ctx, 1); // score
  const char * value = duk_to_string(_ctx, 2); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetIncrby(key_h, score, RMS_Value, &flags, &newScore);
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  if (ret == REDISMODULE_OK) {
    duk_push_number(_ctx, newScore);
  } else {
    duk_push_undefined(_ctx);
  }
  return 1;
}

duk_ret_t zset_incrby_if_present(duk_context *_ctx) {
  int flags = REDISMODULE_ZADD_XX;
  double newScore;
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_double_t score = duk_require_number(_ctx, 1); // score
  const char * value = duk_to_string(_ctx, 2); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetIncrby(key_h, score, RMS_Value, &flags, &newScore);
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);
  if (ret == REDISMODULE_OK && flags != REDISMODULE_ZADD_NOP) {
    duk_push_number(_ctx, newScore);
  } else {
    duk_push_undefined(_ctx);
  }
  return 1;
}

duk_ret_t zset_incrby_if_absent(duk_context *_ctx) {
  int flags = REDISMODULE_ZADD_NX;
  double newScore;
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_double_t score = duk_require_number(_ctx, 1); // score
  const char * value = duk_to_string(_ctx, 2); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetIncrby(key_h, score, RMS_Value, &flags, &newScore);
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  if (ret == REDISMODULE_OK && flags != REDISMODULE_ZADD_NOP) {
    duk_push_number(_ctx, newScore);
  } else {
    duk_push_undefined(_ctx);
  }
  return 1;
}

duk_ret_t zset_rem(duk_context *_ctx) {
  int deleted;
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * value = duk_to_string(_ctx, 1); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetRem(key_h, RMS_Value, &deleted);
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  if (ret == REDISMODULE_OK) {
    duk_push_boolean(_ctx, deleted);
  } else {
    duk_push_undefined(_ctx);
  }
  return 1;
}

duk_ret_t zset_score(duk_context *_ctx){
  double score;
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * value = duk_to_string(_ctx, 1); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetScore(key_h, RMS_Value, &score);
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  if (ret == REDISMODULE_OK) {
    duk_push_number(_ctx, score);
  } else {
    duk_push_undefined(_ctx);
  }
  return 1;
}

double get_number_or_default(duk_context *_ctx, duk_idx_t idx, double _default) {
  if (duk_is_undefined(_ctx, idx)) return _default;
  return duk_require_number(_ctx, idx);
}

duk_ret_t zset_range_stop(duk_context *_ctx) {
  RedisModuleKey * key_h = (RedisModuleKey *) duk_require_pointer(_ctx, 0); // key
  RedisModule_ZsetRangeStop(key_h);
  RedisModule_CloseKey(key_h);  
  return 0;
}

duk_ret_t zset_range_end_reached(duk_context *_ctx) {
  RedisModuleKey * key_h = (RedisModuleKey *) duk_require_pointer(_ctx, 0); // key
  int ret = RedisModule_ZsetRangeEndReached(key_h);
  duk_push_boolean(_ctx, ret);
  return 1;
}

duk_ret_t zset_start_range_n(duk_context *_ctx, int (*func)(RedisModuleKey*, double, double, int, int)) {
  const char * key = duk_require_string(_ctx, 0); // key name
  double min = get_number_or_default(_ctx, 1, REDISMODULE_NEGATIVE_INFINITE);
  double max = get_number_or_default(_ctx, 2, REDISMODULE_POSITIVE_INFINITE);
  duk_bool_t min_inc = duk_require_boolean(_ctx, 3);
  duk_bool_t max_inc = duk_require_boolean(_ctx, 4);

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
  if (key_h == NULL) {
    duk_push_undefined(_ctx);
    RedisModule_FreeString(RM_ctx, RMS_Key);
    return 1;
  }

  int ret = func(key_h, min, max, !min_inc, !max_inc); 

  RedisModule_FreeString(RM_ctx, RMS_Key);

  if (ret == REDISMODULE_OK) {
    duk_push_pointer(_ctx, key_h);
  } else {
    RedisModule_CloseKey(key_h);
    duk_push_undefined(_ctx);
  }
  return 1;
}

duk_ret_t zset_first_in_score_range(duk_context *_ctx) {
  int ret = zset_start_range_n(_ctx, RedisModule_ZsetFirstInScoreRange);
}

duk_ret_t zset_last_in_score_range(duk_context *_ctx)  {
  int ret = zset_start_range_n(_ctx, RedisModule_ZsetLastInScoreRange);
}

duk_ret_t zset_start_range_l(duk_context *_ctx, int (*func)(RedisModuleKey*, RedisModuleString*, RedisModuleString*)) {
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * min = duk_require_string(_ctx, 1);
  const char * max = duk_require_string(_ctx, 2);
  
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Min = RedisModule_CreateString(RM_ctx, min, strlen(min));
  RedisModuleString *RMS_Max = RedisModule_CreateString(RM_ctx, max, strlen(max));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
  if (key_h == NULL) {
    duk_push_undefined(_ctx);
    RedisModule_FreeString(RM_ctx, RMS_Key);
    RedisModule_FreeString(RM_ctx, RMS_Min);
    RedisModule_FreeString(RM_ctx, RMS_Max);
    return 1;
  }

  int ret = func(key_h, RMS_Min, RMS_Max); 

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Min);
  RedisModule_FreeString(RM_ctx, RMS_Max);

  if (ret == REDISMODULE_OK) {
    duk_push_pointer(_ctx, key_h);
  } else {
    RedisModule_CloseKey(key_h);
    duk_push_undefined(_ctx);
  }
  return 1;
}

duk_ret_t zset_first_in_lex_range(duk_context *_ctx)  {
  int ret = zset_start_range_l(_ctx, RedisModule_ZsetFirstInLexRange);
}

duk_ret_t zset_last_in_lex_range(duk_context *_ctx)  {
  int ret = zset_start_range_l(_ctx, RedisModule_ZsetLastInLexRange);
}

duk_ret_t zset_range_current_element(duk_context *_ctx) {
  RedisModuleKey * key_h = (RedisModuleKey *) duk_require_pointer(_ctx, 0); // key
  double score;
  RedisModuleString * value = RedisModule_ZsetRangeCurrentElement(key_h, &score);
  if (value == NULL) {
    duk_push_undefined(_ctx);
    return 1;
  }
  duk_idx_t obj_idx = duk_push_object(_ctx);
  duk_push_number(_ctx, score);
  duk_put_prop_string(_ctx, obj_idx, "score");
  size_t len;
  duk_push_string(_ctx, RedisModule_StringPtrLen(value,&len));
  duk_put_prop_string(_ctx, obj_idx, "key");
  RedisModule_FreeString(RM_ctx, value);
  return 1;
}

duk_ret_t zset_range_next(duk_context *_ctx) {
  RedisModuleKey * key_h = (RedisModuleKey *) duk_require_pointer(_ctx, 0); // key
  int ret = RedisModule_ZsetRangeNext(key_h);
  duk_push_boolean(_ctx, ret);
  return 1;
}

duk_ret_t zset_range_prev(duk_context *_ctx) {
  RedisModuleKey * key_h = (RedisModuleKey *) duk_require_pointer(_ctx, 0); // key
  int ret = RedisModule_ZsetRangePrev(key_h);
  duk_push_boolean(_ctx, ret);
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

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
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

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
  return 1;
}

duk_ret_t hash_update_if_present(duk_context *_ctx){
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

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
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

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
  return 1;
}

duk_ret_t hash_is_set(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  int exists;
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);

  if (key_h == NULL) {
    duk_pop(_ctx);
    duk_push_undefined(_ctx);
    RedisModule_FreeString(RM_ctx, RMS_Key);
    return 1;
  }

  RedisModule_HashGet(key_h, REDISMODULE_HASH_CFIELDS | REDISMODULE_HASH_EXISTS, hashkey, &exists, NULL);
  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);
  duk_push_boolean(_ctx, exists);
  RedisModule_FreeString(RM_ctx, RMS_Key);
  return 1;
}

duk_ret_t hash_get(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_HashValue;

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
  if (key_h == NULL) {
    duk_pop(_ctx);
    duk_push_undefined(_ctx);
    RedisModule_FreeString(RM_ctx, RMS_Key);
    return 1;
  }

  size_t len;
  RedisModule_HashGet(key_h, REDISMODULE_HASH_CFIELDS, hashkey, &RMS_HashValue, NULL);
  RedisModule_CloseKey(key_h);
  duk_pop(_ctx);
  duk_push_string(_ctx, RedisModule_StringPtrLen(RMS_HashValue, &len));
  RedisModule_FreeString(RM_ctx, RMS_HashValue);
  RedisModule_FreeString(RM_ctx, RMS_Key);

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

duk_ret_t set_auto_replication(duk_context *_ctx){
  auto_replication = duk_require_boolean(_ctx, 0); 
  return 0;
}

duk_ret_t get_auto_replication(duk_context *_ctx){
  duk_push_boolean(_ctx, auto_replication); 
  return 1;
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
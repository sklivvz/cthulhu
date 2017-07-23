// Copyright 2017 Marco Cecconi
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "commands.h"
#include "../lib/redismodule.h"
#include "../lib/duktape.h"

duk_ret_t zset_add(duk_context *_ctx) {
  int flags = 0;
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_double_t score = duk_require_number(_ctx, 1); // score
  const char * value = duk_to_string(_ctx, 2); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetAdd(key_h, score, RMS_Value, &flags);

  if (auto_replication){
    char output[50];
    snprintf(output, 50, "%f", score);
    int res = RedisModule_Replicate(RM_ctx, "ZADD", "scs", RMS_Key, output, RMS_Value);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_Value);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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

  if (auto_replication){
    char output[50];
    snprintf(output, 50, "%f", score);
    int res = RedisModule_Replicate(RM_ctx, "ZADD", "cscs", "XX", RMS_Key, output, RMS_Value);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_Value);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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
  if (auto_replication){
    char output[50];
    snprintf(output, 50, "%f", score);
    int res = RedisModule_Replicate(RM_ctx, "ZADD", "cscs", "NX", RMS_Key, output, RMS_Value);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_Value);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }
  RedisModule_CloseKey(key_h);

  duk_pop(_ctx);

  RedisModule_FreeString(RM_ctx, RMS_Key);
  RedisModule_FreeString(RM_ctx, RMS_Value);

  duk_push_boolean(_ctx, (ret == REDISMODULE_OK && flags != REDISMODULE_ZADD_NOP));
  return 1;
}

duk_ret_t zset_incrby(duk_context *_ctx) {
  int flags = 0;
  double newScore;
  const char * key = duk_require_string(_ctx, 0); // key name
  duk_double_t score = duk_require_number(_ctx, 1); // score
  const char * value = duk_to_string(_ctx, 2); // ele

  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_Value = RedisModule_CreateString(RM_ctx, value, strlen(value));

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);
  int ret = RedisModule_ZsetIncrby(key_h, score, RMS_Value, &flags, &newScore);
  if (auto_replication){
    char output[50];
    snprintf(output, 50, "%f", score);
    int res = RedisModule_Replicate(RM_ctx, "ZINCRBY", "scs", RMS_Key, output, RMS_Value);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_Value);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }
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
  if (auto_replication && flags != REDISMODULE_ZADD_NOP){
    char output[50];
    snprintf(output, 50, "%f", score);
    int res = RedisModule_Replicate(RM_ctx, "ZINCRBY", "scs", RMS_Key, output, RMS_Value);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_Value);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }
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
  if (auto_replication){
    char output[50];
    snprintf(output, 50, "%f", score);
    int res = RedisModule_Replicate(RM_ctx, "ZINCRBY", "cscs", "NX", RMS_Key, output, RMS_Value);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_Value);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }
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
  if (auto_replication){
    int res = RedisModule_Replicate(RM_ctx, "ZREM", "ss", RMS_Key, RMS_Value);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_Value);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }
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

  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_READ);
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
  if (RedisModule_KeyType(key_h) != REDISMODULE_KEYTYPE_ZSET) return 0;
  RedisModule_CloseKey(key_h);  
  return 0;
}

duk_ret_t zset_range_end_reached(duk_context *_ctx) {
  RedisModuleKey * key_h = (RedisModuleKey *) duk_require_pointer(_ctx, 0); // key
  if (RedisModule_KeyType(key_h) != REDISMODULE_KEYTYPE_ZSET) {
    duk_push_undefined(_ctx);
    return 1;
  }
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
  if (RedisModule_KeyType(key_h) != REDISMODULE_KEYTYPE_ZSET) {
    duk_push_undefined(_ctx);
    return 1;
  }
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
  if (RedisModule_KeyType(key_h) != REDISMODULE_KEYTYPE_ZSET) {
    duk_push_undefined(_ctx);
    return 1;
  }
  int ret = RedisModule_ZsetRangeNext(key_h);
  duk_push_boolean(_ctx, ret);
  return 1;
}

duk_ret_t zset_range_prev(duk_context *_ctx) {
  RedisModuleKey * key_h = (RedisModuleKey *) duk_require_pointer(_ctx, 0); // key
  if (RedisModule_KeyType(key_h) != REDISMODULE_KEYTYPE_ZSET) {
    duk_push_undefined(_ctx);
    return 1;
  }
  int ret = RedisModule_ZsetRangePrev(key_h);
  duk_push_boolean(_ctx, ret);
  return 1;
}

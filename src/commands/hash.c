
// Copyright 2017 Marco Cecconi
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "commands.h"
#include "../lib/redismodule.h"
#include "../lib/duktape.h"


duk_ret_t hash_set(duk_context *_ctx){
  const char * key = duk_require_string(_ctx, 0); // key name
  const char * hashkey = duk_to_string(_ctx, 1); // hash key
  const char * hashvalue = duk_to_string(_ctx, 2); // hash value
  RedisModuleString *RMS_Key = RedisModule_CreateString(RM_ctx, key, strlen(key));
  RedisModuleString *RMS_HashValue = RedisModule_CreateString(RM_ctx, hashvalue, strlen(hashvalue));
  void *key_h = RedisModule_OpenKey(RM_ctx, RMS_Key, REDISMODULE_WRITE);

  int ret = RedisModule_HashSet(key_h, REDISMODULE_HASH_NONE | REDISMODULE_HASH_CFIELDS, hashkey, RMS_HashValue, NULL);
  if (auto_replication){
    int res = RedisModule_Replicate(RM_ctx, "HSET", "scs", RMS_Key, hashkey, RMS_HashValue);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_HashValue);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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

  if (auto_replication){
    int res = RedisModule_Replicate(RM_ctx, "HSETNX", "scs", RMS_Key, hashkey, RMS_HashValue);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_HashValue);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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

  if (auto_replication){
    // not *exactly* the same, but it should have the same effect
    int res = RedisModule_Replicate(RM_ctx, "HSET", "scs", RMS_Key, hashkey, RMS_HashValue);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      RedisModule_FreeString(RM_ctx, RMS_HashValue);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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
  if (auto_replication){
    int res = RedisModule_Replicate(RM_ctx, "HDEL", "sc", RMS_Key, hashkey);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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
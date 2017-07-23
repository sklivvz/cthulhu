// Copyright 2017 Marco Cecconi
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "commands.h"
#include "../lib/redismodule.h"
#include "../lib/duktape.h"

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

  if (auto_replication) {
    int res = RedisModule_Replicate(RM_ctx, "SELECT", "l", newid);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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

  if (auto_replication) {
    int res = RedisModule_Replicate(RM_ctx, "DEL", "s", RMS_Key);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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

  if (auto_replication) {
    int res = RedisModule_Replicate(RM_ctx, "EXPIRE", "sl", RMS_Key, expire);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "error", "replication failed");
      RedisModule_CloseKey(key_h);
      RedisModule_FreeString(RM_ctx, RMS_Key);
      return duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

  RedisModule_CloseKey(key_h);
  RedisModule_FreeString(RM_ctx, RMS_Key);

  duk_push_boolean(_ctx, ret == REDISMODULE_OK);
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

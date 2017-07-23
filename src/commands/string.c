
// Copyright 2017 Marco Cecconi
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "commands.h"
#include "../lib/redismodule.h"
#include "../lib/duktape.h"

duk_ret_t test(duk_context *_ctx) {
  RedisModule_Replicate(RM_ctx, "SET", "cc", "foo", "0");
  int res = RedisModule_Replicate(RM_ctx, "ZINCRBY", "cccc", "XX", "CTHULHU", "0.666", "SHOGGOTH");
  RedisModule_Log(RM_ctx, "notice", "The call returned: %d", res);
  return 0;
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

  if (auto_replication) {
    int res = RedisModule_Replicate(RM_ctx, "SET", "cc", key, value);
    if (res == REDISMODULE_ERR) {
      RedisModule_Log(RM_ctx, "warning", "replication failed");
      duk_error(_ctx, DUK_ERR_TYPE_ERROR, "replication failed");
    }
  }

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

// Copyright 2017 Marco Cecconi
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "lib/redismodule.h"
#include "lib/duktape.h"
#include "commands/commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

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
    fclose(f);
    RedisModule_Free(source);
    source = NULL;
    duk_push_undefined(_ctx);
    return -2;
  } 
  fclose(f);
  duk_push_lstring(_ctx, (const char *) source, (duk_size_t) size);
  RedisModule_Free(source);
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
  
  _ctx = duk_create_heap_default();
  if (!_ctx) {
    RedisModule_Log(ctx, "warning", "Failed to create a Duktape heap.\n");
    return REDISMODULE_ERR;
  }

  register_commands(_ctx);

  char *path = strdup(filename);
  if (path == NULL) {
    RedisModule_Log(ctx, "warning", "Out of memory.\n");
    return REDISMODULE_ERR;
  }
  char *dir = dirname(path);

  char *js;
  if (asprintf(&js, "%s/cthulhu.js", dir) < 0) {
    free(path);
    RedisModule_Log(ctx, "warning", "Out of memory.\n");
    return REDISMODULE_ERR;
  }

  RedisModule_Log(ctx, "notice", "Loading `%s'...", js);
  if (load_file_to_context(_ctx, js)<0) {
    free(js);
    free(path);
    RedisModule_Log(ctx, "warning", "Could not read file.\n");
    return REDISMODULE_ERR;
  }
  free(js);
  free(path);

  if (duk_peval(_ctx) != 0) {
    RedisModule_Log(ctx, "warning", "Compile failed: %s\n", duk_safe_to_string(_ctx, -1));
    return REDISMODULE_ERR;
  }

  RedisModule_Log(ctx, "notice", "Loading `%s'...", filename);
  if (load_file_to_context(_ctx, filename)<0) return REDISMODULE_ERR;

  if (duk_peval(_ctx) != 0) {
    RedisModule_Log(ctx, "warning", "Compile failed: %s\n", duk_safe_to_string(_ctx, -1));
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
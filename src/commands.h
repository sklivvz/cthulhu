
// Copyright 2017 Marco Cecconi
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#if !defined(CTHULHU_COMMANDS_INCLUDED)
#define CTHULHU_COMMANDS_INCLUDED

#include "redismodule.h"
#include "duktape.h"

duk_context *_ctx;
RedisModuleCtx *RM_ctx;

duk_ret_t milliseconds(duk_context *_ctx);
duk_ret_t get_client_id(duk_context *_ctx);
duk_ret_t get_selected_db(duk_context *_ctx);
duk_ret_t select_db(duk_context *_ctx);
duk_ret_t length(duk_context *_ctx);
duk_ret_t delete_key(duk_context *_ctx);
duk_ret_t get_expire(duk_context *_ctx);
duk_ret_t set_expire(duk_context *_ctx);
duk_ret_t string_set(duk_context *_ctx);
duk_ret_t string_truncate(duk_context *_ctx);
duk_ret_t string_get(duk_context *_ctx);
duk_ret_t list_push(duk_context *_ctx);
duk_ret_t list_pop(duk_context *_ctx);
duk_ret_t zset_add(duk_context *_ctx);
duk_ret_t zset_add_if_absent(duk_context *_ctx);
duk_ret_t zset_update_if_present(duk_context *_ctx);
duk_ret_t zset_incrby(duk_context *_ctx);
duk_ret_t zset_incrby_if_absent(duk_context *_ctx);
duk_ret_t zset_incrby_if_present(duk_context *_ctx);
duk_ret_t zset_rem(duk_context *_ctx);
duk_ret_t zset_score(duk_context *_ctx);
duk_ret_t zset_range_stop(duk_context *_ctx);
duk_ret_t zset_range_end_reached(duk_context *_ctx);
duk_ret_t zset_first_in_score_range(duk_context *_ctx);
duk_ret_t zset_last_in_score_range(duk_context *_ctx);
duk_ret_t zset_first_in_lex_range(duk_context *_ctx);
duk_ret_t zset_last_in_lex_range(duk_context *_ctx);
duk_ret_t zset_range_current_element(duk_context *_ctx);
duk_ret_t zset_range_next(duk_context *_ctx);
duk_ret_t zset_range_prev(duk_context *_ctx);
duk_ret_t hash_set(duk_context *_ctx);
duk_ret_t hash_update_if_present(duk_context *_ctx);
duk_ret_t hash_set_if_absent(duk_context *_ctx);
duk_ret_t hash_unset(duk_context *_ctx);
duk_ret_t hash_is_set(duk_context *_ctx);
duk_ret_t hash_get(duk_context *_ctx);
duk_ret_t log_to_redis(duk_context *_ctx);

int load_file_to_context(duk_context *_ctx, const char *filename);

void register_commands(duk_context *_ctx);

#endif  /* CTHULHU_COMMANDS_INCLUDED */
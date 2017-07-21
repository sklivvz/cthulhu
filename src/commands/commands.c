
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
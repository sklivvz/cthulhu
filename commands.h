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
duk_ret_t list_push(duk_context *_ctx);
duk_ret_t list_pop(duk_context *_ctx);
// duk_ret_t zset_add(duk_context *_ctx);
// duk_ret_t zset_incrby(duk_context *_ctx);
// duk_ret_t zset_rem(duk_context *_ctx);
// duk_ret_t zset_score(duk_context *_ctx);
// duk_ret_t zset_range_stop(duk_context *_ctx);
// duk_ret_t zset_range_end_reached(duk_context *_ctx);
// duk_ret_t zset_first_in_score_range(duk_context *_ctx);
// duk_ret_t zset_last_in_score_range(duk_context *_ctx);
// duk_ret_t zset_first_in_lex_range(duk_context *_ctx);
// duk_ret_t zset_last_in_lex_range(duk_context *_ctx);
// duk_ret_t zset_range_current_element(duk_context *_ctx);
// duk_ret_t zset_range_next(duk_context *_ctx);
// duk_ret_t zset_range_prev(duk_context *_ctx);
// duk_ret_t hash_set(duk_context *_ctx);
// duk_ret_t hash_get(duk_context *_ctx);
duk_ret_t log_to_redis(duk_context *_ctx);

int load_file_to_context(duk_context *_ctx, const char *filename);

void register_commands(duk_context *_ctx);

#endif  /* CTHULHU_COMMANDS_INCLUDED */
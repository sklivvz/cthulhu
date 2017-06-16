# Cthulhu
Extend Redis with JavaScript modules

![](https://c1.staticflickr.com/9/8758/18161295638_6fc93ec641_b.jpg)

This module *invokes commands* from Redis in a JavaScript interpreter (*the thing that should not be*)

*there is nothing to see here*

*seriously*

*it's broken*



*like, you need to patch Redis first*

## Redis API

This are the `RedisModule` APIs that are planned for version 0.1:

 * [x] milliseconds
 * [x] get_client_id
 * [x] get_selected_db
 * [x] select_db
 * [x] length
 * [x] delete_key
 * [x] get_expire
 * [x] set_expire
 * [x] string_set
 * [x] string_truncate
 * [x] string_get
 * [x] list_push
 * [x] list_pop
 * [ ] zset_add
 * [ ] zset_incrby
 * [ ] zset_rem
 * [ ] zset_score
 * [ ] zset_range_stop
 * [ ] zset_range_end_reached
 * [ ] zset_first_in_score_range
 * [ ] zset_last_in_score_range
 * [ ] zset_first_in_lex_range
 * [ ] zset_last_in_lex_range
 * [ ] zset_range_current_element
 * [ ] zset_range_next
 * [ ] zset_range_prev
 * [x] hash_set
 * [x] hash_set_if_present
 * [x] hash_set_if_absent
 * [x] hash_unset
 * [x] hash_is_set
 * [x] hash_get
 * [x] log

 They are documented in the [Redis Module API page](https://github.com/antirez/redis/blob/unstable/src/modules/API.md)

### Roadmap

* create an actual JavaScript API and not simply global methods
* blocking calls/background processing
* functions with variable argument number
* return type to redis should be specific and not string
* support for generic LUA style calls

 ## Version

 The current version is 0.0.

 ## License

 [BSD 3-Clause](https://github.com/sklivvz/cthulhu/blob/master/LICENSE)
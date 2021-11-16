#include "endpoints.h"

#include <ulfius.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jansson.h>

#define STRINGS_LEN 5
/**
 * @brief map the post request to a useable value
 *
 * @param map
 * @return Endpoint*
 */
Endpoint *map_request(const struct _u_map *map) {
  const char **keys, *value;
  KV *temp_kv_pair;
  KVSet *kv_set = malloc(sizeof(KVSet));
  kv_set->count = 0;
  printf("body_count: %d\n", map->nb_values);

  keys = u_map_enum_keys(map);
  for (int i = 0; keys[i] != NULL; i++) {
    printf("iterating\n");
    temp_kv_pair = malloc(sizeof(KV));
    value = u_map_get(map, keys[i]);
    temp_kv_pair->key = memcpy(temp_kv_pair->key, keys[i],
                               sizeof(strlen(keys[i]) * sizeof(char)));
    temp_kv_pair->value = memcpy(temp_kv_pair->value, value,
                                 sizeof(strlen(value) * sizeof(char)));
    kv_set->count++;
    kv_set->kvs = realloc(kv_set->kvs, (kv_set->count + 1) * sizeof(KV *));
    kv_set->kvs[kv_set->count - 1] =
        memcpy(kv_set->kvs[kv_set->count - 1], temp_kv_pair, sizeof(KV));
  }
  return map_kv_set(kv_set);
}
/**
 * @brief transform a kvset into the endpoint
 *
 * @param set
 * @return Endpoint*
 */
Endpoint *map_kv_set(KVSet *set) {

  Endpoint *return_me = calloc(1, sizeof(Endpoint));
  return_me->ip = "none";
  bool bad_req = false;
  printf("count %d \n", set->count);
  if (set->count < STRINGS_LEN) {
    return return_me;
  }
  for (int i = 0; i < set->count; i++) {
    if (strcmp(set->kvs[i]->key, "ip") == 0) {
      free(return_me->ip);
      return_me->ip = memcpy(set->kvs[i]->value, return_me->ip,
                             (strlen((set->kvs[i]->value)) * sizeof(char)));
    } else if (strcmp(set->kvs[i]->key, "busy") == 0) {
      if (strcmp(set->kvs[i]->value, "true") == 0) {
        return_me->busy = true;
      } else {
        return_me->busy = false;
      }
    } else if (strcmp(set->kvs[i]->key, "cores") == 0) {
      int as_int = atoi(set->kvs[i]->value);
      if (as_int == 0) {
        goto ret_null;
      }
      return_me->cores = as_int;
    } else if (strcmp(set->kvs[i]->key, "speed") == 0) {
      int as_int = atoi(set->kvs[i]->value);
      if (as_int == 0) {
        goto ret_null;
      }
      return_me->speed = as_int;
    } else if (strcmp(set->kvs[i]->key, "ram") == 0) {
      int as_int = atoi(set->kvs[i]->value);
      if (as_int == 0) {
        goto ret_null;
      }
      return_me->ram = as_int;
    } else {
    ret_null:
      bad_req = true;
    }
    free(set->kvs[i]->key);
    free(set->kvs[i]->value);
  }
  free(set->kvs);
  free(set);
  if (bad_req) {
    free(return_me->ip);
    free(return_me);
    return NULL;
  }
  return return_me;
}
/**
 * @brief print values in a _u_map
 *
 * @param map
 */
void print_mapped_values(struct _u_map *map) {
  int count = map->nb_values;
  printf("count %d \n", count);
  for (int i = 0; i < count; i++) {
    printf("key: %s, value: %s \n", map->keys[i], map->values[i]);
  }
}

void print_json_kvs(json_t *json) {
  printf("printing json\n");
  if (json == NULL) {
    printf("json is null\n");
  }
  printf("the json type is: %d\n", json->type);
  switch (json->type) {
  case 0:
    printf("json is an object\n");
    const char *key;
    json_t *value;
    json_object_foreach(json, key, value) {
      if (value->type > 1) {
        printf("key:  %s \nValue: %s \n", key, json_string_value(value));
      }
    }
  }

  // do some other stuff
}

// TODO this takes values in x-www-form-urlencoded make this use json
/**
 * @brief the endpoint for a post request to "/post"
 *
 * @param request
 * @param response
 * @param user_data
 * @return int
 */
int post_endpoint(const struct _u_request *request,
                  struct _u_response *response, void *user_data) {
  printf("url path: %s\n", request->url_path);
  print_mapped_values(request->map_header);
  printf("mapping the header stuff\n");
  print_mapped_values(request->map_post_body);
  json_error_t *error = NULL;
  json_t *json = ulfius_get_json_body_request(request, error);
  if (error == NULL) {
    print_json_kvs(json);
  } else {
    printf("error occurred: %s", error->text);
  }

  // Endpoint *end = map_request(request->map_post_body);
  char *response_body;
  /*if (strcmp(end->ip, "none") == 0)
  {
    response_body = "bad post request";
  }*/
  // else
  //{
  response_body = "done";
  //}
  ulfius_set_string_body_response(response, 200, response_body);
  return U_CALLBACK_CONTINUE;
}

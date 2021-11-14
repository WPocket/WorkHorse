#include "endpoints.h"

#include <ulfius.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRINGS_LEN 5

Endpoint *map_request(const struct _u_map *map)
{
    const char **keys, *value;
    KV *temp_kv_pair;
    KVSet *kv_set = malloc(sizeof(KVSet));
    if (map == NULL)
    {
        return NULL;
    }

    keys = u_map_enum_keys(map);
    for (int i = 0; keys[i] != NULL; i++)
    {
        temp_kv_pair = malloc(sizeof(KV));
        value = u_map_get(map, keys[i]);
        temp_kv_pair->key = memcpy(temp_kv_pair->key, keys[i], sizeof(strlen(keys[i]) * sizeof(char)));
        temp_kv_pair->value = memcpy(temp_kv_pair->value, value, sizeof(strlen(value) * sizeof(char)));
        kv_set->count++;
        kv_set->kvs = realloc(kv_set->kvs, (kv_set->count + 1) * sizeof(KV *));
        kv_set->kvs[kv_set->count - 1] = memcpy(kv_set->kvs[kv_set->count - 1], temp_kv_pair, sizeof(KV));
    }
    return map_kv_set(kv_set);
}

Endpoint *map_kv_set(KVSet *set)
{
    
    Endpoint *return_me = calloc(1, sizeof(Endpoint));
    return_me->ip = "none";
    bool bad_req = false;
    for (int i = 0; i < set->count; i++)
    {
        if (strcmp(set->kvs[i]->key, "ip") == 0)
        {
            free(return_me->ip);
            return_me->ip = memcpy(set->kvs[i]->value, return_me->ip, (strlen((set->kvs[i]->value)) * sizeof(char)));
        }
        else if (strcmp(set->kvs[i]->key, "busy") == 0)
        {
            if (strcmp(set->kvs[i]->value, "true") == 0)
            {
                return_me->busy = true;
            }
            else
            {
                return_me->busy = false;
            }
        }
        else if (strcmp(set->kvs[i]->key, "cores") == 0)
        {
            int as_int = atoi(set->kvs[i]->value);
            if (as_int == 0)
            {
                goto ret_null;
            }
            return_me->cores = as_int;
        }
        else if (strcmp(set->kvs[i]->key, "speed") == 0)
        {
            int as_int = atoi(set->kvs[i]->value);
            if (as_int == 0)
            {
                goto ret_null;
            }
            return_me->speed = as_int;
        }
        else if (strcmp(set->kvs[i]->key, "ram") == 0)
        {
            int as_int = atoi(set->kvs[i]->value);
            if (as_int == 0)
            {
                goto ret_null;
            }
            return_me->ram = as_int;
        }
        else
        {
        ret_null:
            bad_req = true;
        }
        free(set->kvs[i]->key);
        free(set->kvs[i]->value);
    }
    free(set->kvs);
    free(set);
    if (bad_req)
    {
        free(return_me->ip);
        free(return_me);
        return NULL;
    }
    return return_me;
}

int post_endpoint(const struct _u_request *request, struct _u_response *response, void *user_data)
{
    Endpoint *end = map_request(request->map_post_body);
    char *response_body;
    if (strcmp(end->ip, "none") == 0)
    {
        response_body = "bad post request";
    }
    else
    {
        response_body = "success";
    }
    ulfius_set_string_body_response(response, 200, response_body);
    return U_CALLBACK_CONTINUE;
}
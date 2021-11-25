#include "endpoints.h"

#include <ulfius.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jansson.h>

#define is_string

#define STRINGS_LEN 5
Endpoint *json_to_endpoint(json_t *json) {
  if (json->type != 0) {
    return NULL;
  }
  // map it into an endpoint
  Endpoint *endpt = malloc(sizeof(Endpoint));
  json_t *value;

  // attempt to build an endpoint definition
  // get ip
  value = json_object_get(json, "ip");
  if (value == NULL || value->type != JSON_STRING) {
    goto free_endpt;
  }
  const char *temporary = json_string_value(value);
  if (temporary == NULL) {
    goto free_endpt;
  }

  endpt->ip = strdup(temporary);

  // get busy
  value = json_object_get(json, "busy");
  if (value == NULL ||
      (value->type != JSON_TRUE && value->type != JSON_FALSE)) {
    free(endpt->ip);
    goto free_endpt;
  }

  endpt->busy = (value->type == JSON_TRUE);

  // get cores
  value = json_object_get(json, "cores");
  if (value == NULL || value->type != JSON_INTEGER) {
    free(endpt->ip);
    goto free_endpt;
  }

  endpt->cores = json_integer_value(value);
  // get cores
  value = json_object_get(json, "speed");
  if (value == NULL || value->type != JSON_INTEGER) {
    free(endpt->ip);
    goto free_endpt;
  }

  endpt->speed = json_integer_value(value);

  // get cores
  value = json_object_get(json, "ram");
  if (value == NULL || value->type != JSON_INTEGER) {
    free(endpt->ip);
    goto free_endpt;
  }

  endpt->ram = json_integer_value(value);

  return endpt;
free_endpt:
  free(endpt);
  return NULL;
}

void print_endpoint(Endpoint *endpoint) {
  printf("{\n");
  printf("\"ip\": \"%s\",\n", endpoint->ip);
  printf("\"busy\": %s,\n", (endpoint->busy) ? "true" : "false");
  printf("\"cores\": %d,\n", endpoint->cores);
  printf("\"speed\": %d,\n", endpoint->speed);
  printf("\"ram\": %d,\n", endpoint->ram);
  printf("}\n");
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
  json_error_t *error = NULL;
  json_t *json = ulfius_get_json_body_request(request, error);
  char *response_body;
  if (error == NULL) {
    Endpoint *endpt = json_to_endpoint(json);
    if (endpt == NULL) {
      goto endpt_null;
    }
    // print the endpoint
    print_endpoint(endpt);
    // do a post request.

  } else if (error != NULL) {
    printf("error occurred: %s", error->text);
    response_body = "json error";
  } else {
  endpt_null:
    response_body = "error";
  }

  ulfius_set_string_body_response(response, 200, response_body);
  return U_CALLBACK_CONTINUE;
}

bool send_data(Endpoint *endpt) { return false; }

#include "endpoints.h"

#include <ulfius.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jansson.h>

#define STRINGS_LEN 5
Endpoint *json_to_endpoint(json_t *json) {
  if (json->type != 0) {
    return NULL;
  }
  // map it into an endpoint
  Endpoint *endpt = malloc(sizeof(Endpoint));
  const char *key;
  json_t *value;
  json_object_foreach(json, key, value) {
    if (json->type == JSON_STRING) {
      // something with string
      printf("key: %s \n Value: %s \n", key, json_string_value(value));
    }
  }
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
  if (error == NULL) {
    json_to_endpoint(json);
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

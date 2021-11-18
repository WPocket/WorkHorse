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
  json_t *value = json_object_get(json, "ip");
  if (value == NULL) {
    printf("value is null\n");
    return NULL;

  } else if (value->type != JSON_STRING) {

    printf("value is not a string\n");
    return NULL;
  } else {
    endpt->ip = strdup(json_string_value(value));
    if (endpt->ip == NULL) {
      goto free_endpt;
    }
    return endpt;
  free_endpt:
    free(endpt);
    return NULL;
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
  char *response_body;
  if (error == NULL) {
    Endpoint *endpt = json_to_endpoint(json);
    if (endpt == NULL) {
      goto endpt_null;
    }
    printf("the value of ip is: %s\n", endpt->ip);
    response_body = strdup(endpt->ip);

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

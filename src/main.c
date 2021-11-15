#include "main.h"

#include <ulfius.h>

#include <stdio.h>
#include <string.h>

#include "endpoints.h"

#define PORT 8080

int main(int argc, char **argv) {
  struct _u_instance instance;

  int ret;

  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort");
    return (1);
  }

  register_config(&instance);
  // Start the framework

  ret = ulfius_start_framework(&instance);

  if (ret == U_OK) {
    printf("Start %sframework on port %d",
           ((argc == 4 && strcmp("-secure", argv[1]) == 0) ? "secure " : ""),
           instance.port);

    // Wait for the user to press <enter> on the console to quit the application
    getchar();
  } else {
    printf("Error starting framework");
  }
  printf("End framework");

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);

  return 0;
}

void register_config(struct _u_instance *instance) {

  ulfius_add_endpoint_by_val(instance, "POST", "/post", NULL, 0, &post_endpoint,
                             NULL);
}

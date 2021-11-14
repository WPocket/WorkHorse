#include "main.h"

#include <ulfius.h>

#include <stdio.h>

#include "get_endpoints.h"

#define PORT 8080

int main(void) {
  struct _u_instance instance;

  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort");
    return (1);
  }

  register_config(&instance);
}

void register_config(struct _u_instance *instance) {}

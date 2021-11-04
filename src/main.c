#include "main.h"

#include <stdio.h>

#include <ulfius.h>

#define PORT 8080

int main(void) {
  struct _u_instance instance;

  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort");
    return (1);
  }
}

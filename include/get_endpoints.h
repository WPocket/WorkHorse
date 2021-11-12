#ifndef GET_ENDPOINTS_H
#define GET_ENDPOINTS_H

#include <stdbool.h>

#include <ulfius.h>

typedef struct {
	char *ip;
	bool busy;
	int cores;
	int speed;
	int ram;
} Endpoint;



#endif

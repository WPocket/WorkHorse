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

typedef struct {
	Endpoint *endpoints;
	int count;
} Endpoints;

// TODO use memcopy for this
void addEndpoint(Endpoint* endpoint);

void delEndpoint(int index);

Endpoint* getBestFree(Endpoints endpoints);

Endpoints* getEndpoints(char* db_address, struct _u_instance *instance, int db_index);

#endif

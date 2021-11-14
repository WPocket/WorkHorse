#ifndef ENDPOINTS_H
#define ENDPOINTS_H

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
	char * key;
	char * value;
} KV;

typedef struct {
	int count;
	KV** kvs;
} KVSet;

Endpoint * map_request(const struct _u_map * map);
Endpoint * map_kv_set(KVSet * set);

int post_endpoint(const struct _u_request * request, struct _u_response * response, void * user_data);


#endif

#ifndef ENDPOINTS_H
#define ENDPOINTS_H

#include <stdbool.h>

#include <ulfius.h>


typedef struct {
	char *ip; /** the ip of the host*/
	bool busy; /** is this host busy*/
	int cores; /** number of cores*/
	int speed;/** the speed of the processor*/
	int ram; /** the amount of ram*/
	/**
 	* @brief all the information on a new endpoint
 	* 
 	*/
} Endpoint;


typedef struct {
	char * key; /** the key*/
	char * value; /** the value*/
	/**
	 * @brief a key and value combination
	 * 
	 */
} KV;

typedef struct {
	int count;/** the number of kv pairs */
	KV** kvs; /**the kv pairs as a 1d pointer array*/
	/**
	 * @brief a set containing multiple key value pairs
	 * 
	 */
} KVSet;

Endpoint * json_to_endpoint(json_t *json);

int post_endpoint(const struct _u_request * request, struct _u_response * response, void * user_data);


#endif

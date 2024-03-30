#include <string.h>
#include "request.h"
#include "main.h"

struct Request parse_request(char* str) {
	struct Request request;
	int str_len = strlen(str);

	char* method = str;
	char* url = strchr(method, ' ') + 1;
	char* version = strchr(url, ' ') + 1;
	char* headers = strchr(version, '\n') + 1;
	char* body = strstr(headers, "\n\n") + 1;

	*(url - 1) = 0;
	*(version - 1) = 0;
	*(headers - 1) = 0;
	*(body - 1) = 0;

	if (strcmp("GET", method)) {
		request.method = GET;
	} else if (strcmp("HEAD", method)) {
		request.method = HEAD;
	} else if (strcmp("POST", method)) {
		request.method = POST;
	} else if (strcmp("PUT", method)) {
		request.method = PUT;
	} else if (strcmp("DELETE", method)) {
		request.method = DELETE;
	} else if (strcmp("CONNECT", method)) {
		request.method = CONNECT;
	} else if (strcmp("OPTIONS", method)) {
		request.method = OPTIONS;
	} else if (strcmp("TRACE", method)) {
		request.method = TRACE;
	} else if (strcmp("PATCH", method)) {
		request.method = PATCH;
	} else {
		request.method = -1;
	}

	return request;
}

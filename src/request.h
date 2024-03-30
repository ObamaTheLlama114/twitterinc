#pragma once

#include "main.h"

enum HttpMethod {
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE,
	PATCH,
};

struct Request {
	enum HttpMethod method;
	char* url;
	char* version;
	struct Headers headers;
	char* body;
};

struct Request parse_request(char* str);

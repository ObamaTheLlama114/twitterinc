#pragma once

struct Header {
	char* key;
	char* value;
};

struct Headers {
	struct Header* headers_p;
	int headers_count;
};


typedef struct Response (*HandlerFunc)(struct Request request);

#pragma once

#include "main.h"

struct Response {
	char* version;
	int status_code;
	char* status_text;
	struct Headers headers;
	char* body;
};


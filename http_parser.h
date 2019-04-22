
#ifndef HTTP_PARSER_H_
#define HTTP_PARSER_H_


enum http_method {
	GET = 1,
	POST = 2,
	HEAD = 3,
	OPTION = 4,
	DELETE = 5,
	PUT = 6,
	PATCH = 7
};

enum http_version {
	V1_1 = 1,
	V2 = 2
};

struct http_request {
	enum http_method method;
	enum http_version version;


};

#endif

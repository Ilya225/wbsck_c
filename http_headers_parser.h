/*
 * http_headers_parser.h
 *
 *  Created on: Apr 20, 2019
 *      Author: illia
 */

#ifndef HTTP_HEADERS_PARSER_H_
#define HTTP_HEADERS_PARSER_H_


enum http_headers_parsing_state {
	INIT = 0,
	CR = 1,
	CRLF = 2,
	END_OF_LINE = 3,
	END_OF_LINE_CR = 4,
	END_OF_HEADERS = 5,
	NOT_MATCH = -1
};

void set_initial_state();
enum http_headers_parsing_state parse_request(char *request_buffer, int size);


#endif /* HTTP_HEADERS_PARSER_H_ */

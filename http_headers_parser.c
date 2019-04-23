/*
 * http_headers_parser.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: illia
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "http_headers_parser.h"
#include "linked_list.h"

/** prototypes **/
void set_input(char input);
enum http_headers_parsing_state get_state();

/** initializations **/

static enum http_headers_parsing_state state;
static string_list headers;

/** implementation code **/

enum http_headers_parsing_state parse_request(char *request_buffer, int size) {

	int i = 0 ,str_begin = 0;
	char *p = request_buffer;

	string_list *next_line = &headers;

	set_initial_state();
	while (i < size) {
		set_input(p[i]);
		if (state == END_OF_LINE) {
			int line_size = i - 1 - str_begin;
			next_line->string = (char*) malloc(line_size * sizeof(char));
			memcpy(next_line->string, &(p[i - 1 - line_size]), line_size);
			next_line->next = malloc(sizeof(string_list));
			next_line = next_line->next;
			str_begin = i;
		} else if (state == END_OF_HEADERS) {
			return END_OF_HEADERS;
		}
		i++;
	}

	state = NOT_MATCH;

	return state;
}

void set_input(char input) {

	switch (state) {
	case INIT:
		if (input == '\r') {
			state = CR;
		}
		break;
	case CR:
		if (input == '\n') {
			state = CRLF;
		}
		break;
	case CRLF:
		if (input == '\r') {
			state = END_OF_LINE_CR;
		} else {
			state = END_OF_LINE;
		}
		break;
	case END_OF_LINE_CR:
		if (input == '\n') {
			state = END_OF_HEADERS;
		}
		break;
	case END_OF_LINE:
		state = INIT;
	default:
		break;
	}
}

void set_initial_state() {
	state = INIT;
}

enum http_headers_parsing_state get_state() {
	return state;
}

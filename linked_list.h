/*
 * linked_list.h
 *
 *  Created on: Apr 20, 2019
 *      Author: illia
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_


struct string_list {
	char *string;
	struct string_list *next;
};

typedef struct string_list string_list;


#endif /* LINKED_LIST_H_ */

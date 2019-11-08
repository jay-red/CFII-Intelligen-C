#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <cstdlib>

typedef struct {
	unsigned int size;
	unsigned int length;
	void** arr;
} ArrayList;

void initialize_list( ArrayList *list );

void push_back_list( ArrayList *list, void* element );

void push_front_list( ArrayList *list, void* element );

void insert_list( ArrayList *list, unsigned int index, void* element );

void* get_list( ArrayList *list, unsigned int index );

void set_list( ArrayList *list, unsigned int index, void* element );

void remove_list( ArrayList *list, unsigned int index );

void clear_list( ArrayList *list );

#endif

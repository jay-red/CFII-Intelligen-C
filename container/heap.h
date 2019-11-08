#ifndef HEAP_H
#define HEAP_H

#include "arraylist.h"

typedef struct {
	ArrayList* data;
	unsigned char ( *compare )( void* ptr1, void* ptr2 );
} Heap;

void initialize_heap( Heap* heap, unsigned char( *compare )( void* ptr1, void* ptr2 ) );

void push_heap( Heap* heap, void* element );

void pop_heap( Heap* heap );

void* top_heap( Heap* heap );

#endif

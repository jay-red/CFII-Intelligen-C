#ifndef HEAP_H
#define HEAP_H

typedef struct {
	ArrayList* data;
	signed char ( *compare )( void* ptr1, void* ptr2 );
} Heap;

void initialize_heap( Heap* heap, signed char( *compare )( void* ptr1, void* ptr2 ) );

void push_heap( Heap* heap );

void pop_heap( Heap* heap );

void* top_heap( Heap* heap );

#endif

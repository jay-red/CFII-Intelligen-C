// heap.cc
#include "heap.h"

void initialize_heap( Heap* heap, unsigned char( *compare )( void* ptr1, void* ptr2 ) ) {
	heap->data = ( ArrayList* ) malloc( sizeof( ArrayList ) );
	heap->compare = compare;
	initialize_list( heap->data );
	push_back_list( heap->data, 0 );
}

void push_heap( Heap* heap, void* element ) {
	push_back_list( heap->data, element );
	unsigned int childIndex = heap->data->length - 1;
	unsigned int parentIndex = childIndex >> 1;
	while( parentIndex >= 1 && heap->compare( element, get_list( heap->data, parentIndex ) ) ) {
		set_list( heap->data, childIndex, get_list( heap->data, parentIndex ) );
		set_list( heap->data, parentIndex, element );
		childIndex = parentIndex;
		parentIndex = childIndex >> 1;
	}
}

void pop_heap( Heap* heap ) {
	unsigned int length = heap->data->length;
	if( length > 1 ) {
		set_list( heap->data, 1, get_list( heap->data, length - 1 ) );
		remove_list( heap->data, length - 1 );
		--length;
		if( length == 1 ) return;

		unsigned int index = 1, parentIndex = 1, leftIndex = 2, rightIndex = 3;
		void* ptr, *parentPtr, *leftPtr, *rightPtr;
		unsigned char heapify = 1;
		while( heapify ) {
			heapify = 0;
			ptr = get_list( heap->data, index );
			parentPtr = ptr;
			leftPtr = get_list( heap->data, leftIndex );
			rightPtr = get_list( heap->data, rightIndex );
			if( ptr && leftPtr ) {
				if( heap->compare( leftPtr, ptr ) ) {
					ptr = leftPtr;
					index = leftIndex;
					heapify = 1;
				}
				if( rightPtr && heap->compare( rightPtr, ptr ) ) {
					ptr = rightPtr;
					index = rightIndex;
					heapify = 1;
				}
				if( heapify ) {
					set_list( heap->data, parentIndex, ptr );
					set_list( heap->data, index, parentPtr );
					parentIndex = index;
					leftIndex = index * 2;
					rightIndex = index * 2 + 1;		
				}
			}
		}
	} 	
}

void* top_heap( Heap* heap ) {
	return get_list( heap->data, 1 );
}

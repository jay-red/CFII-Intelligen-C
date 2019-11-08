// arraylist.cc
#include "arraylist.h"

void initialize_list( ArrayList *list ) {
	list->size = 1;
	list->length = 0;
	list->arr = ( void** ) malloc( sizeof( void* ) );
	*( list->arr ) = 0;
}

void push_back_list( ArrayList *list, void* element ) {
	if( list->size == list->length ) {
		list->size = list->size << 1;
		list->arr = ( void** ) realloc( list->arr, list->size * sizeof( void* ) );
		for( unsigned int i = list->length; i < list->size; i++ ) {
			*( list->arr + i ) = 0;
		}
	}
	*( list->arr + list->length ) = element;
	list->length++;
}

void push_front_list( ArrayList *list, void* element );

void insert_list( ArrayList *list, unsigned int index, void* element ) {
	/*
	if( index == list->length ) pushBackList( list, element );
	else if( index < list->size ) {
		for( unsigned int i = list->length; i < list->length; i++ ) {
			
		}
	}
	*/
}

void* get_list( ArrayList *list, unsigned int index ) {
	if( index < list->length ) return *( list->arr + index );
	else return 0;
}

void set_list( ArrayList *list, unsigned int index, void* element ) {
	if( index == list->length ) push_back_list( list, element );
	else if( index < list->length ) {
		*( list->arr + index ) = element;
	}
}

void remove_list( ArrayList *list, unsigned int index ) {

}

void clear_list( ArrayList *list ) {
	list->size = 0;
}

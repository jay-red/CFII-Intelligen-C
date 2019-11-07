// arraylist.cc
#include "arraylist.h"

void initializeList( ArrayList *list ) {
	list->size = 1;
	list->length = 0;
	list->arr = ( void** ) malloc( sizeof( void* ) );
}

void pushBackList( ArrayList *list, void* element ) {
	if( list->size == list->length ) {
		list->size = list->size << 1;
		list->arr = ( void** ) realloc( list->arr, list->size * sizeof( void* ) );
	}
	*( list->arr + list->length ) = element;
	list->length++;
}

void pushFrontList( ArrayList *list, void* element );

void insertList( ArrayList *list, unsigned int index, void* element );

void* getList( ArrayList *list, unsigned int index ) {
	if( index < list->size ) {
		return *( list->arr + index );
	} else {
		return 0;
	}
}

void setList( ArrayList *list, unsigned int index, void* element );

void removeList( ArrayList *list, unsigned int index );


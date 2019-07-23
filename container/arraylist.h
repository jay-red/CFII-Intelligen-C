#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct {
	unsigned int size;
	unsigned int length;
	void** arr;
} ArrayList;

void initializeList();

void pushBackList( ArrayList *list, void* element );

void pushFrontList( ArrayList *list, void* element );

void insertList( ArrayList *list, unsigned int index, void* element );

void* getList( ArrayList *list, unsigned int index );

void setList( ArrayList *list, unsigned int index, void* element );

void removeList( ArrayList *list, unsigned int index );

#endif

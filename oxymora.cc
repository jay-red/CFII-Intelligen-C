#include <stdlib.h>
#include <stdio.h>

#include "container/jstring.h"
#include "container/heap.h"
#include "enigma/enigma.h"

int main() {
	JString test = initializeJStr( "hello world hello" );
	printf( "%X\n", *test );
	setJStr( test, "hello world 2!" );
	printf( "%X\n", *test );
	printf( "%u\n", lenJStr( test ) );
	printf( "%s", toString_JStr( test ) );
	int t = JoinGame();
	return 0;
}

#include <stdlib.h>
#include <stdio.h>

#include "container/jstring.h"
#include "container/heap.h"
#include "enigma/enigma.h"

int main() {
	JString test = initializeJStr( "hello world" );
	setJStr( test, "hello world 2!" );
	printf( "%u", lenJStr( test ) );
	int t = JoinGame();
	return 0;
}

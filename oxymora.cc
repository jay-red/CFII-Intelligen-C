#include <stdlib.h>
#include <stdio.h>

#include "container/jstring.h"
#include "container/heap.h"
#include "enigma/enigma.h"

int main() {
	JString test = initializeJStr( "hello world hello" );
	int t = JoinGame();
	return 0;
}

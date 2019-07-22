#include <stdlib.h>
#include <stdio.h>

#include "container/heap.h"
#include "enigma/enigma.h"

int main() {
	Enigma* game = initializeEnigma( "public" );
	JString j = initializeJStr( "" );
	appendJStr( j, 'c' );	
	appendJStr( j, 'u' );	
	appendJStr( j, 't' );	
	appendJStr( j, 'e' );	
	appendJStr( j, '!' );	
	printf( "%u\n", equalJStr( j, "cute" ) );
	printf( "%s\n", toString_JStr( j ) );
	if( JoinGame( game, "Enigma", "CuteButDeadly" ) ) {
		Refresh( game );
		return 0;
	} else {
		return 1;
	}
}

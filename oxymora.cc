#include <stdlib.h>
#include <stdio.h>

#include "container/heap.h"
#include "enigma/enigma.h"

int main() {
	Enigma* game = initializeEnigma( "public" );
	JString j = initializeJStr( "" );
	catJStr( j, "Cute" );	
	catJStr( j, "But" );	
	catJStr( j, "Deadly" );	
	printf( "%u\n", lenJStr( j ) );
	printf( "%s\n", toString_JStr( j ) );
	if( JoinGame( game, "Enigma", "CuteButDeadly" ) ) {
		Refresh( game );
		return 0;
	} else {
		return 1;
	}
}

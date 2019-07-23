#include <stdlib.h>
#include <stdio.h>

#include "container/heap.h"
#include "enigma/enigma.h"

int main() {
	Enigma* game = initializeEnigma( "public" );
	if( JoinGame( game, "Enigma", "CuteButDeadly" ) ) {
		Refresh( game );
		printf( "Turn:%u\n", GetCell( game, 0, 16 )->building );
		terminateEnigma( game );
		return 0;
	} else {
		return 1;
	}
}

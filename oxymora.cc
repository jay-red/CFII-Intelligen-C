#include <stdlib.h>
#include <stdio.h>

#include "container/heap.h"
#include "enigma/enigma.h"

int main() {
	Enigma* game = initializeEnigma();
	if( JoinGame( game ) ) {
		return 0;
	} else {
		return 1;
	}
}

#include <stdlib.h>
#include <stdio.h>

#include "oxymora.h"

int main() {
	ArrayList a;
	initialize_list( &a );
	int s = 2;
	int s3 = 3;
	push_back_list( &a, &s );
	push_back_list( &a, &s3 );
	void* p = get_list( &a, 0 ); 
	if( p ) {
	printf( "%d\n", *( ( int* ) p ) );
	}
	Enigma* game = ( Enigma* ) malloc( sizeof( Enigma ) );
	initialize_enigma( game, "public" );
	if( JoinGame( game, "Enigma", "CuteButDeadly" ) ) {
		Refresh( game );
		printf( "Turn:%u\n", GetCell( game, 27, 4 )->building );
		terminate_enigma( game );
		return 0;
	} else {
		return 1;
	}
}

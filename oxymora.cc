#include <stdlib.h>
#include <stdio.h>

#include "oxymora.h"

unsigned char compare( void* ptr1, void* ptr2 ) {
	return *( ( int* ) ptr1 ) > *( ( int* ) ptr2 );
}

int main() {
	int s0 = 0;
	int s1 = 1;
	int s2 = 2;
	int s3 = 3;
	int s4 = 4;
	int s5 = 5;
	int s6 = 6;
	int s7 = 7;
	int s8 = 8;
	int s9 = 9;
	
	Heap h;
	initialize_heap( &h, compare );

	push_heap( &h, &s5 );
	push_heap( &h, &s9 );
	push_heap( &h, &s0 );
	push_heap( &h, &s3 );
	push_heap( &h, &s1 );
	push_heap( &h, &s7 );
	push_heap( &h, &s2 );
	push_heap( &h, &s8 );
	push_heap( &h, &s6 );
	push_heap( &h, &s4 );

	void* i = top_heap( &h );
	while( i ) {
		printf( "%d\n", *( ( int* ) i ) );
	       	pop_heap( &h );
		i = top_heap( &h );
	}
	Enigma* game = ( Enigma* ) malloc( sizeof( Enigma ) );
		printf( "%d\n",  1004 );
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

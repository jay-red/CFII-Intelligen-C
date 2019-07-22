// parse.cc

#include <stdlib.h>
#include <stdio.h>
#include "enigma.h"

void parseGame( Enigma* game ) {
	CString* buffer = ( CString* ) malloc( sizeof( CString ) );
	*buffer = toString_JStr( game->gameBuffer );
	for( ; **buffer != '\0'; ( *buffer )++ ) {
		printf( "%c", **buffer );
	}
}

void parseInfo( Enigma* game, CString* buffer ) {

}

void parseErrorArr( Enigma* game, CString* buffer ) {

}

void parseError( Enigma* game, CString* buffer ) {

}

void parseMap( Enigma* game, CString* buffer ) {

}

void parseCellArr( Enigma* game, CString* buffer ) {

}

void parseCell( Enigma* game, CString* buffer ) {

}

void parseHeaderArr( Enigma* game, CString* buffer ) {

}

void parseUserArr( Enigma* game, CString* buffer ) {

}

void parseUser( Enigma* game, CString* buffer ) {

}

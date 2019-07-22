// parse.cc

#include "enigma.h"
#include "parse.h"

void parseGame( Enigma* game ) {
	CString* buffer = ( CString* ) malloc( sizeof( CString ) );
	*buffer = toString_JStr( game->gameBuffer );
	char keyFlag = 0;
	if( **buffer != '{' ) return;
	char depth = 0;
	for( ; **buffer != '\0'; ( *buffer )++ ) {
		if( **buffer == '{' ) ++depth;
		else if( **buffer == '}' ) --depth;
		if( depth == 1 ) {
			if( **buffer == '"' ) {
				if( keyFlag ) {
					keyFlag = 0;
					printf( "%s\n", toString_JStr( game->parseBuffer ) );

				} else {
					keyFlag = 1;
					setJStr( game->parseBuffer, "" );
				}
			} else if( keyFlag ) {
				appendJStr( game->parseBuffer, **buffer );
			}
		}
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

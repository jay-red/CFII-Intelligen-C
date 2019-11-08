// parse.cc

#include "enigma.h"
#include "parse.h"

void parseNum( Enigma* game, CString* buffer ) {
	for( ; **buffer == ' ' || **buffer == ':' || **buffer == '"'; ++( *buffer ) );
	setJStr( game->parseBuffer, "" );
	for( ; **buffer != ',' && **buffer != '}' && **buffer != ']'; ++( *buffer ) ) {
		appendJStr( game->parseBuffer, **buffer );
	}
}

char parseChar( Enigma* game, CString* buffer ) {
	parseNum( game, buffer );
	return atoi( toString_JStr( game->parseBuffer ) );
}

unsigned short parseShort( Enigma* game, CString* buffer ) {
	parseNum( game, buffer );
	return atoi( toString_JStr( game->parseBuffer ) );
}

void parseGame( Enigma* game ) {
	CString* buffer;
	buffer = ( CString* ) malloc( sizeof( CString* ) );
	
	CString str = ( CString ) malloc( sizeof( CString ) * ( lenJStr( game->gameBuffer ) + 1 ) );
	*buffer = str;

	memcpy( ( void* ) *buffer, toString_JStr( game->gameBuffer ), lenJStr( game->gameBuffer ) + 1 );
	char keyFlag = 0;
	if( **buffer != '{' ) return;
	char depth = 0;
	for( ; **buffer != '\0'; ++( *buffer ) ) {
		if( **buffer == '{' ) ++depth;
		else if( **buffer == '}' ) --depth;
		if( depth == 1 ) {
			if( **buffer == '"' ) {
				if( keyFlag ) {
					keyFlag = 0;
					//printf( "%s", toString_JStr( game->parseBuffer ) );
					if( equalJStr( game->parseBuffer, "turn" ) ) {
						game->turn = parseShort( game, buffer );
					} else if( equalJStr( game->parseBuffer, "info" ) ) {
						parseInfo( game, buffer );	
					} else if( equalJStr( game->parseBuffer, "error" ) ) {
						parseErrorArr( game, buffer );	
					} else if( equalJStr( game->parseBuffer, "game_map" ) ) {
						//printf( "%c\n", **buffer );
						for( ; **buffer == ' ' || **buffer == ':' || **buffer == '"' || **buffer == '{'; ++( *buffer ) );
						++depth;
						if( **buffer == 'd' ) {
							*buffer += 4;
							parseCellArr( game, buffer );
							parseHeaderArr( game, buffer );
						} else if( **buffer == 'h' ) { 
							*buffer += 7;
							parseHeaderArr( game, buffer );
							parseCellArr( game, buffer );
						}
					} else if( equalJStr( game->parseBuffer, "users" ) ) {
						parseUserArr( game, buffer );
					}	
					//printf( "\n" );
				} else {
					keyFlag = 1;
					setJStr( game->parseBuffer, "" );
				}
			} else if( keyFlag ) {
				appendJStr( game->parseBuffer, **buffer );
			}
		}
	}
	free( ( void* ) str );
	free( buffer );
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
	for( ; **buffer != '['; ++( *buffer ) );
	char depth = 0;
	for( ; **buffer != '\0'; ++( *buffer ) ) {
		if( **buffer == '[' ) ++depth;
		else if( **buffer == ']' ) --depth;
		if( depth == 0 ) return;
		else if( depth == 3 ) {
			parseCell( game, buffer );
			depth = 2;
		}
	}
}

void parseCell( Enigma* game, CString* buffer ) {
	*buffer += 1;
	unsigned short attack_cost = parseShort( game, buffer );
	*buffer += 1;
	unsigned short force_field = parseShort( game, buffer );
	for( ; **buffer != '"'; ++( *buffer ) );
	*buffer += 1;
	char building = 0;
	if( **buffer == ' ' ) {
		building = 0;
	} else if( **buffer == 'h' ) {
		building = 3;
	} else if( **buffer == 'g' ) {
		building = 6;
	} else if( **buffer == 'e' ) {
		building = 9;
	} else if( **buffer == 'f' ) {
		building = 12;
	}
	*buffer += 3;
	building += parseChar( game, buffer ) - 1;
	for( ; **buffer != ','; ++( *buffer ) );
	*buffer += 1;
	char gold = parseChar( game, buffer ) ;
	*buffer += 1;
	char energy = parseChar( game, buffer );
	*buffer += 1;
	char owner = parseChar( game, buffer );
	*buffer += 1;
	unsigned short index = 0;
	for( ; **buffer != '['; ++( *buffer ) );
	*buffer += 1;
	unsigned char x = parseChar( game, buffer );
	index += x;
	*buffer += 2;
	unsigned char y = parseChar( game, buffer );
	index += 30 * y;
	for( ; **buffer != ','; ++( *buffer ) );
	*buffer += 1;
	char natural_gold = parseChar( game, buffer );
	*buffer += 1;
	char natural_energy = parseChar( game, buffer );
	*buffer += 1;
	unsigned short natural_cost = parseShort( game, buffer );
	for( ; **buffer != ']'; ++( *buffer ) );
	game->cells[ index ].x = x;
	game->cells[ index ].y = y;
	game->cells[ index ].attack_cost = attack_cost;
	game->cells[ index ].force_field = force_field;
	game->cells[ index ].building = building;
	game->cells[ index ].gold = gold;
	game->cells[ index ].energy = energy;
	game->cells[ index ].owner = owner;
	game->cells[ index ].natural_gold = natural_gold;
	game->cells[ index ].natural_energy = natural_energy;
	game->cells[ index ].natural_cost = natural_cost;
}

void parseHeaderArr( Enigma* game, CString* buffer ) {

}

void parseUserArr( Enigma* game, CString* buffer ) {
	for( ; **buffer != '['; ++( *buffer ) );
	char depth = 0;
	for( ; **buffer != '\0'; ++( *buffer ) ) {
		if( **buffer == '[' ) ++depth;
		else if( **buffer == ']' ) --depth;
		if( depth == 0 ) return;
		else if( depth == 3 ) {
			//parseCell( game, buffer );
		}
	}
}

void parseUser( Enigma* game, CString* buffer ) {

}

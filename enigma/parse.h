#ifndef PARSE_H
#define PARSE_H

#include "../container/jstring.h"

void parseGame( Enigma* game );

void parseInfo( Enigma* game, CString* buffer );

void parseErrorArr( Enigma* game, CString* buffer );

void parseError( Enigma* game, CString* buffer );

void parseMap( Enigma* game, CString* buffer );

void parseCellArr( Enigma* game, CString *buffer );

void parseCell( Enigma* game, CString* buffer );

void parseHeaderArr( Enigma* game, CString* buffer );

void parseUserArr( Enigma* game, CString* buffer );

void parseUser( Enigma* game, CString* buffer );

#endif

#ifndef ENIGMA_H
#define ENGIMA_H

#include "../container/jstring.h"
#include "../network/network_c.h"

#include "cell.h"
#include "user.h"

typedef struct {
	JString gameBuffer;
	JString actionBuffer;
	JString parseBuffer;
	JString cmdBuffer;
	WebSocket* ws;
	Cell* cells;
	User* users;
	unsigned short turn;
	unsigned short gameCid;
	unsigned short actionCid;
} Enigma;

Enigma* initializeEnigma( CString const room );

void terminateEnigma( Enigma* game );

int JoinGame( Enigma* game, CString const name, CString const password );

void Refresh( Enigma* game );

Cell* GetCell( Enigma *game, char x, char y );

#endif

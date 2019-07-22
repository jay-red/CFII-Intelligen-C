#ifndef ENIGMA_H
#define ENGIMA_H

#include "../container/jstring.h"
#include "../network/network_c.h"

#include "cell.h"

typedef struct {
	unsigned short turn;
	unsigned short gameCid;
	unsigned short actionCid;
	JString gameBuffer;
	JString actionBuffer;
	JString parseBuffer;
	JString cmdBuffer;
	WebSocket* ws;
	Cell* cells;
} Enigma;

Enigma* initializeEnigma( CString const room );

void terminateEnigma( Enigma* game );

int JoinGame( Enigma* game, CString const name, CString const password );

void Refresh( Enigma* game );

#endif

#ifndef ENIGMA_H
#define ENGIMA_H

#include "../container/jstring.h"
#include "../network/network_c.h"

typedef struct {
	unsigned short gameCid;
	unsigned short actionCid;
	JString gameBuffer;
	JString actionBuffer;
	WebSocket* ws;
} Enigma;

Enigma* initializeEnigma();

int JoinGame( Enigma* game );

#endif

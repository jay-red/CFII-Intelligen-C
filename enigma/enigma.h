#ifndef ENIGMA_H
#define ENGIMA_H

#include "../container/jstring.h"
#include "../container/arraylist.h"
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
	ArrayList* commands;
	unsigned int commandIndex = 0;
	unsigned short turn;
	unsigned short gameCid;
	unsigned short actionCid;
} Enigma;

void initialize_enigma( Enigma* game, CString const room );

void terminate_enigma( Enigma* game );

int JoinGame( Enigma* game, CString const name, CString const password );

void Refresh( Enigma* game );

Cell* GetCell( Enigma *game, char x, char y );

void BeginTurn( Enigma* game );

void EndTurn( Enigma* game );

void AppendNumToJStr( JString jstr, unsigned int num );

void Command( Enigma *game, unsigned char x, unsigned char y );

void Attack( Enigma* game, unsigned char x, unsigned char y, unsigned int energy );

void Build( Enigma* game, unsigned char x, unsigned char y, unsigned char building );

void Upgrade( Enigma* game, unsigned char x, unsigned char y );

#endif

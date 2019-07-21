#include <stdlib.h>
#include <stdio.h>
#include "enigma.h"
#include "../network/network_c.h"

Enigma* initializeEnigma() {
	Enigma* game = ( Enigma* ) malloc( sizeof( Enigma ) );
	game->ws = initializeWS();
	game->gameBuffer = initializeJStr("");
	game->actionBuffer = initializeJStr("");
	game->gameCid = wsOpen( game->ws, "wss://colorfightai.com/gameroom/public/game_channel", game->gameBuffer );
	game->actionCid = wsOpen( game->ws, "wss://colorfightai.com/gameroom/public/action_channel", game->actionBuffer );
	while( lenJStr( game->gameBuffer ) == 0 );
	return game;
}

int JoinGame( Enigma* game ) {
	while( lenJStr( game->actionBuffer ) == 0 ) {
		wsSend( game->ws, game->actionCid, "{\"action\":\"register\",\"username\":\"Enigma\",\"password\":\"last-agnikai\",\"join_key\":\"\"}" );
	}
	printf("%s\n", toString_JStr( game->actionBuffer ) );
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "enigma.h"
#include "parse.h"
#include "../network/network_c.h"

Enigma* initializeEnigma( CString const room ) {
	Enigma* game = ( Enigma* ) malloc( sizeof( Enigma ) );
	game->turn = 0;
	game->cells = ( Cell* ) malloc( sizeof( Cell ) * 900 );
	game->ws = initializeWS();
	game->gameBuffer = initializeJStr("");
	game->actionBuffer = initializeJStr("");
	game->parseBuffer = initializeJStr("");
	game->cmdBuffer = initializeJStr("");
	game->gameCid = wsOpen( game->ws, "wss://colorfightai.com/gameroom/public/game_channel", game->gameBuffer );
	game->actionCid = wsOpen( game->ws, "wss://colorfightai.com/gameroom/public/action_channel", game->actionBuffer );
	while( lenJStr( game->gameBuffer ) == 0 );
	return game;
}

void terminateEnigma( Enigma* game ) {
	free( game->cells );
	terminateWS( game->ws );
	terminateJStr( game->gameBuffer );
	terminateJStr( game->actionBuffer );
	terminateJStr( game->parseBuffer );
	terminateJStr( game->cmdBuffer );
}

int JoinGame( Enigma* game, CString const name, CString const pass ) {
	while( lenJStr( game->actionBuffer ) == 0 ) {
		wsSend( game->ws, game->actionCid, "{\"action\":\"register\",\"username\":\"Enigma\",\"password\":\"last-agnikai\",\"join_key\":\"\"}" );
	}
	printf("%s\n", toString_JStr( game->actionBuffer ) );
	return 1;
}

void Refresh( Enigma* game ) {	
	parseGame( game );
}

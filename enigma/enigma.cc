#include <stdlib.h>
#include <stdio.h>
#include "enigma.h"
#include "parse.h"
#include "../network/network_c.h"

void initialize_enigma( Enigma* game, CString const room ) {
	game->turn = 0;
	game->cells = ( Cell* ) malloc( sizeof( Cell ) * 900 );
	game->users = ( User* ) malloc( sizeof( User ) );
	game->ws = initializeWS();
	game->gameBuffer = initializeJStr("");
	game->actionBuffer = initializeJStr("");
	game->parseBuffer = initializeJStr("");
	game->cmdBuffer = initializeJStr("");
	game->commands = ( ArrayList* ) malloc( sizeof( ArrayList ) );
	game->commandIndex = 0;
	initialize_list( game->commands );
	game->gameCid = wsOpen( game->ws, "wss://colorfightai.com/gameroom/public/game_channel", game->gameBuffer );
	game->actionCid = wsOpen( game->ws, "wss://colorfightai.com/gameroom/public/action_channel", game->actionBuffer );
	while( lenJStr( game->gameBuffer ) == 0 );
}

void terminate_enigma( Enigma* game ) {
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

Cell* GetCell( Enigma* game, char x, char y ) {
	return game->cells + ( ( 30 * y ) + x );
}

void StartTurn( Enigma* game ) {

}

void EndTurn( Enigma* game ) {

}

void AppendNumToJStr( JString jstr, unsigned int num ) {
	if( num / 10 == 0 ) {
	
	} else {
		AppendNumToJStr( jstr, num / 10 );
	}
}

void Command( Enigma* game, unsigned char x, unsigned char y ) {
	void* ptr = get_list( game->commands, game->commandIndex );
	JString cmdStr;
	if( ptr ) {
		cmdStr = ( JString ) ptr;
	} else {
		cmdStr = initializeJStr( "" );
	}
	setJStr( cmdStr, "" );

}

void Attack( Enigma* game, unsigned char x, unsigned char y, unsigned int energy ) {

}

void Build( Enigma* game, unsigned char x, unsigned char y, unsigned char building ) {

}

void Upgrade( Enigma* game, unsigned char x, unsigned char y ) {

}

#include <stdlib.h>
#include <stdio.h>
#include "enigma.h"
#include "parse.h"
#include "../network/network_c.h"

void initialize_enigma( Enigma* game, CString const room ) {
	game->turn = 0;
	game->cells = ( Cell* ) malloc( sizeof( Cell ) * 900 );
	game->users = ( User* ) malloc( sizeof( User ) );
	game->me = 0;
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

unsigned char JoinGame( Enigma* game, CString const name, CString const pass ) {
	setJStr( game->cmdBuffer, "{\"action\":\"register\",\"username\":\"" );
	catJStr( game->cmdBuffer, name );
	catJStr( game->cmdBuffer, "\",\"password\":\"" );
	catJStr( game->cmdBuffer, pass );
	catJStr( game->cmdBuffer, "\",\"join_key\":\"\"}" );
	while( lenJStr( game->actionBuffer ) == 0 ) {
		wsSend( game->ws, game->actionCid, toString_JStr( game->cmdBuffer ) );
		usleep( 20000 );
	}
	CString temp = toString_JStr( game->actionBuffer );
	unsigned int i = 0;
	for( ; temp[ i ] != '\0' && ( temp[ i ] < '0' || temp[ i ] > '9' ); ++i ); 
	i = temp[ i ] - '0';
	game->me = game->users + i;
	game->me->uid = i;
	printf( "%s\n", toString_JStr( game->actionBuffer ) );
	return 1;
}

void Refresh( Enigma* game ) {	
	parseGame( game );
}

Cell* GetCell( Enigma* game, char x, char y ) {
	if( x < 0 || x >= 30 || y < 0 || y >= 30 ) return 0;
	return game->cells + ( ( 30 * y ) + x );
}

void BeginTurn( Enigma* game ) {
	game->commandIndex = 0;
	setJStr( game->actionBuffer, "" );
}

void EndTurn( Enigma* game ) {
	setJStr( game->cmdBuffer, "{\"action\": \"command\", \"cmd_list\": [\"" );
	JString jstr;
	for( unsigned int i = 0; i < game->commandIndex; i++ ) {
		jstr = (JString) get_list( game->commands, i );
		catJStr( game->cmdBuffer, toString_JStr( jstr ) );
		appendJStr( game->cmdBuffer, '"' );
		if( i < game->commandIndex - 1 ) catJStr( game->cmdBuffer, ", \"" );
	}	
	catJStr( game->cmdBuffer, "]}" );
	while( lenJStr( game->actionBuffer ) == 0 ) {
		wsSend( game->ws, game->actionCid, toString_JStr( game->cmdBuffer ) );
		usleep( 20000 );
	}
}

void AppendNumToJStr( JString jstr, unsigned int num ) {
	if( num / 10 == 0 ) {
		return appendJStr( jstr, '0' + ( num % 10 ) );	
	} else {
		AppendNumToJStr( jstr, num / 10 );
	}
	return appendJStr( jstr, '0' + ( num % 10 ) );	
}

void Command( Enigma* game, unsigned char cmd, unsigned char x, unsigned char y ) {
	void* ptr = get_list( game->commands, game->commandIndex );
	JString cmdStr;
	if( ptr ) {
		cmdStr = ( JString ) ptr;
	} else {
		cmdStr = initializeJStr( "" );
		push_back_list( game->commands, cmdStr );
	}
	setJStr( cmdStr, "" );
	appendJStr( cmdStr, cmd );
	appendJStr( cmdStr, ' ' );
	AppendNumToJStr( cmdStr, x );
	appendJStr( cmdStr, ' ' );
	AppendNumToJStr( cmdStr, y );
	++( game->commandIndex );
}

void Attack( Enigma* game, unsigned char x, unsigned char y, unsigned int energy ) {
	Command( game, 'a', x, y );
	JString jstr = ( JString ) get_list( game->commands, game->commandIndex - 1 );
	appendJStr( jstr, ' ' );
	AppendNumToJStr( jstr, energy );
}

void Build( Enigma* game, unsigned char x, unsigned char y, unsigned char building ) {
	Command( game, 'b', x, y );
}

void Upgrade( Enigma* game, unsigned char x, unsigned char y ) {
	Command( game, 'u', x, y );
}

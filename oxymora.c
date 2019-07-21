#include <stdlib.h>
#include <stdio.h>
#include "enigma/network_c.h"

int main() {
	void *buffer = malloc( sizeof( int ) + ( 50 * sizeof( char ) ) );
	WebSocket* ws = initializeWS( &buffer );
	unsigned short cid = wsOpen( ws, "wss://colorfightai.com/gameroom/public/action_channel" );
	printf( "Passed" );
	while( 1 ) {
		wsSend( ws, cid, "{\"action\":\"register\",\"username\":\"Enigma\",\"password\":\"last-agnikai\",\"join_key\":\"\"}" );
	}
	return 0;
}

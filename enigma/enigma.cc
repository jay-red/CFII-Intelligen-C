#include <stdlib.h>
#include <stdio.h>
#include "../container/jstring.h"
#include "../network/network_c.h"

int JoinGame() {
	JString buffer = initializeJStr("");
	WebSocket* ws = initializeWS( buffer );
	unsigned short cid = wsOpen( ws, "wss://colorfightai.com/gameroom/public/action_channel" );
	while( lenJStr( buffer ) == 0 ) {
		wsSend( ws, cid, "{\"action\":\"register\",\"username\":\"Enigma\",\"password\":\"last-agnikai\",\"join_key\":\"\"}" );
		printf( "Sent\n" );
	}
	printf("%s\n", toString_JStr( buffer ) );
	//wsClose( ws, cid );
	terminateWS( ws );
	terminateJStr( buffer );
	return 0;
}

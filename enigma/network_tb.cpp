#include <iostream>
#include "network.h"

using namespace std;

int main() {
	WebSocket ws;
	int cid = ws.open( "wss://colorfightai.com/gameroom/public/action_channel" );
	while( true ) {
		ws.send( cid, "{\"action\":\"register\",\"username\":\"Enigma\",\"password\":\"last-agnikai\",\"join_key\":\"\"}" );
	}
	return 0;
}

#include <iostream>
#include "network.h"

using namespace std;

int main() {
	WebSocket ws;
	ws.open( "wss://colorfightai.com/gameroom/public/game_channel" );
	return 0;
}

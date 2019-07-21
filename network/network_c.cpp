#include <string>

#include "network.h"
#include "network_c.h"

using std::string;

extern "C" {
	WebSocket* initializeWS() {
		return new WebSocket();
	}

	int wsOpen( WebSocket* ws, char const* const host, JString buffer ) {
		return ws->open( string( host ), buffer );
	}

	void wsSend( WebSocket* ws, unsigned short cid, char const* const message ) {
		ws->send( cid, string( message ) );
	}

	void wsClose( WebSocket* ws, unsigned short cid ) {
		ws->close( cid );
	}
	
	void terminateWS( WebSocket* ws ) {
		delete ws;
	}
}

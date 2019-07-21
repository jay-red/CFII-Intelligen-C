#include <string>

#include "../container/jstring.h"

#include "network.h"
#include "network_c.h"

using std::string;

extern "C" {
	WebSocket* initializeWS( JString buffer ) {
		return new WebSocket( buffer );
	}

	int wsOpen( WebSocket* ws, char const* const host ) {
		return ws->open( string( host ) );
	}

	void wsSend( WebSocket* ws, unsigned short cid, char const* const message ) {
		ws->send( cid, string( message ) );
	}
	
	void terminateWS( WebSocket* ws ) {
		delete ws;
	}
}

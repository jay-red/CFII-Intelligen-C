#ifndef NETWORK_C_H
#define NETWORK_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WebSocket WebSocket;

WebSocket* initializeWS();

int wsOpen( WebSocket* ws, char const* const host, JString buffer );

void wsSend( WebSocket *ws, unsigned short cid, char const* const message );

void wsClose( WebSocket *ws, unsigned short cid );

void terminateWS( WebSocket* ws );

#ifdef __cplusplus
}
#endif

#endif

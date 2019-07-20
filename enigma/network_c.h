#ifndef NETWORK_C_H
#define NETWORK_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WebSocket WebSocket;

WebSocket* initWebSocket();

int wsOpen( char const* const host );

int wsSend( unsigned short, char const* const message );

#ifdef __cplusplus
}
#endif

#endif

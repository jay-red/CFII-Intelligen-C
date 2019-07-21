#ifndef NETWORK_H
#define NETWORK_H

#include <map>
#include <iostream>

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include "../container/jstring.h"

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::connection_hdl conn_hdl;

class WSConnection {
	public:
		typedef websocketpp::lib::shared_ptr<WSConnection> ptr;
		WSConnection( conn_hdl handle, JString buffer );
		void onOpen( client* endpoint, conn_hdl handle );
		void onClose( client* endpoint, conn_hdl handle );
		void onFail( client* endpoint, conn_hdl handle );
		void onMessage( conn_hdl handle, client::message_ptr msg );
		conn_hdl getHandle();
	private:
		conn_hdl handle;
		JString buffer;
};

class WebSocket {
	public:
		WebSocket();
		~WebSocket();
		int open( std::string const& host, JString buffer );
		void send( unsigned short cid, std::string message );
		void close( unsigned short cid );
	private:
		std::map<unsigned short, WSConnection::ptr> connections;
		client endpoint;
		websocketpp::lib::shared_ptr<websocketpp::lib::thread> wsThread;
		unsigned int cid;
};

#endif

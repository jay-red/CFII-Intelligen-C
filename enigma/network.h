#ifndef NETWORK_H
#define NETWORK_H

#include <map>
#include <iostream>

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::connection_hdl conn_hdl;

class WebSocket {
	public:
		WebSocket();
		~WebSocket();
		void on_open( conn_hdl hdl );
		void on_close( conn_hdl hdl );
		void on_fail( conn_hdl hdl );
		void on_message( conn_hdl hdl, client::message_ptr msg );
		int open( std::string const& host );
		void send( unsigned short cid, std::string message );
	private:
		std::map<unsigned short, conn_hdl> connections;
		client endpoint;
		websocketpp::lib::shared_ptr<websocketpp::lib::thread> wsThread;
		unsigned int cid;
};

#endif

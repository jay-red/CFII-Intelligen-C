#ifndef NETWORK_H
#define NETWORK_H

#include <map>

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
	private:
		std::map<int, conn_hdl> connections;
		client endpoint;
};

#endif

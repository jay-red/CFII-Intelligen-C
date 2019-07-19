#include "network.h"

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

WebSocket::WebSocket() {
	// Log everything except message payloads
	this->endpoint.set_access_channels( websocketpp::log::alevel::all );
	this->endpoint.clear_access_channels( websocketpp::log::alevel::frame_payload );
	
	// Initialize ASIO
	this->endpoint.init_asio();
	this->endpoint.start_perpetual();
	
	// Provide handler for tls_init
	this->endpoint.set_tls_init_handler( [ this ]( conn_hdl ) {
		return websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv1);
	} );

	// Register the handlers
	this->endpoint.set_open_handler( bind( &WebSocket::on_open, this, ::_1 ) );
	this->endpoint.set_close_handler( bind( &WebSocket::on_close, this, ::_1 ) );
	this->endpoint.set_fail_handler( bind( &WebSocket::on_fail, this, ::_1 ) );
	this->endpoint.set_message_handler( bind( &WebSocket::on_message, this, ::_1, ::_2 ) );
}

WebSocket::~WebSocket() {
	this->endpoint.stop_perpetual();
}

void WebSocket::on_open( conn_hdl hdl ) {

}

void WebSocket::on_close( conn_hdl hdl ) {

}

void WebSocket::on_fail( conn_hdl hdl ) {

}

void WebSocket::on_message( conn_hdl hdl, client::message_ptr msg ) {

}

int WebSocket::open( std::string const& host ) {
	// Initialize structure for errors
	websocketpp::lib::error_code ec;

	// Get a connection object
	client::connection_ptr conn = endpoint.get_connection( host, ec );

	// Check if any errors exist
	if( ec ) return -1;
	
	// Request a connection
	endpoint.connect( conn );

	// Start the ASIO loop & make a connection
	endpoint.run();
	return 0;
}

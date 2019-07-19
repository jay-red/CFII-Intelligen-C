#include "network.h"

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using std::string;
using std::map;

WebSocket::WebSocket() {
	// Initialize the connection ID counter
	this->cid = 0;

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

	// Start and store the thread
	wsThread = websocketpp::lib::make_shared<websocketpp::lib::thread>( &client::run, &endpoint );
}

WebSocket::~WebSocket() {
	// Stop ASIO loop
	this->endpoint.stop_perpetual();

	// Join the thread on close
	wsThread->join();
}

void WebSocket::on_open( conn_hdl hdl ) {

}

void WebSocket::on_close( conn_hdl hdl ) {

}

void WebSocket::on_fail( conn_hdl hdl ) {

}

void WebSocket::on_message( conn_hdl hdl, client::message_ptr msg ) {
	std::cout << msg->get_payload() << std::endl;	
}

int WebSocket::open( string const& host ) {
	// Initialize structure for errors
	websocketpp::lib::error_code ec;

	// Get a connection object
	client::connection_ptr conn = this->endpoint.get_connection( host, ec );

	// Check if any errors exist
	if( ec ) return -1;
	
	// Store server handle
	this->connections[ this->cid ] = conn->get_handle();

	// Request a connection
	this->endpoint.connect( conn );

	// Return the current connection ID & increment
	return this->cid++;
}

void WebSocket::send( unsigned int cid, string message ) {
	// Verify the connection ID is in the valid range
	if( cid < this->cid ) {
		// Search for the connection in the map
		map<int, conn_hdl>::iterator it = connections.find( cid );

		// Exit if the ID is not a valid connection
		if( it == connections.end() ) return;

		// Initialize structure for errors
		websocketpp::lib::error_code ec;
		
		// Request to send a message
		this->endpoint.send( it->second, message, websocketpp::frame::opcode::text, ec );

		if( ec ) { std::cout << ec.message() << std::endl; }
		else { std::cout << "succ" << std::endl; }
	}
}

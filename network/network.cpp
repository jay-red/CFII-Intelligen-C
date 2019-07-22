#include "network.h"

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::make_shared;
using std::string;
using std::map;

WSConnection::WSConnection( conn_hdl handle, JString buffer ) {
	this->handle = handle;
	this->buffer = buffer;
}

void WSConnection::onOpen( client* endpoint, conn_hdl handle ) {
	std::cout << "Connected" << std::endl;
}

void WSConnection::onClose( client* endpoint, conn_hdl handle ) {
}

void WSConnection::onFail( client* endpoint, conn_hdl handle ) {

}

void WSConnection::onMessage( conn_hdl handle, client::message_ptr msg ) {
	setJStr( this->buffer, msg->get_payload().c_str() );
}

conn_hdl WSConnection::getHandle() {
	return this->handle;
}

WebSocket::WebSocket() {
	// Initialize the connection ID counter
	this->cid = 0;

	// Log everything except message payloads
	//this->endpoint.set_access_channels( websocketpp::log::alevel::all );
	this->endpoint.clear_access_channels( websocketpp::log::alevel::all );
	
	// Initialize ASIO
	this->endpoint.init_asio();
	this->endpoint.start_perpetual();
	
	// Provide handler for tls_init
	this->endpoint.set_tls_init_handler( [ this ]( conn_hdl ) {
		return make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv1);
	} );

	// Start and store the thread
	wsThread = make_shared<websocketpp::lib::thread>( &client::run, &endpoint );
}

WebSocket::~WebSocket() {
	// Stop ASIO loop
	this->endpoint.stop_perpetual();

	for( map<unsigned short, WSConnection::ptr>::iterator it = connections.begin(); it != connections.end(); ++it ) {
		close( it->first );
	}

	this->endpoint.stop();

	// Join the thread on close
	this->wsThread->join();
	this->wsThread.reset();
}

int WebSocket::open( string const& host, JString buffer ) {
	// Initialize structure for errors
	websocketpp::lib::error_code ec;

	// Get a connection object
	client::connection_ptr conn = this->endpoint.get_connection( host, ec );

	// Check if any errors exist
	if( ec ) return -1;
	
	// Store server handle
	WSConnection::ptr wsConn = make_shared<WSConnection>( conn->get_handle(), buffer );
	this->connections[ this->cid ] = wsConn;

	// Register the handlers
	conn->set_open_handler( bind( &WSConnection::onOpen, wsConn, &this->endpoint, ::_1 ) );
	conn->set_close_handler( bind( &WSConnection::onClose, wsConn, &this->endpoint, ::_1 ) );
	conn->set_fail_handler( bind( &WSConnection::onFail, wsConn, &this->endpoint, ::_1 ) );
	conn->set_message_handler( bind( &WSConnection::onMessage, wsConn, ::_1, ::_2 ) );
	
	// Request a connection
	this->endpoint.connect( conn );

	// Return the current connection ID & increment
	return this->cid++;
}

void WebSocket::send( unsigned short cid, string message ) {
	// Verify the connection ID is in the valid range
	if( cid < this->cid ) {
		// Search for the connection in the map
		map<unsigned short, WSConnection::ptr>::iterator it = connections.find( cid );

		// Exit if the ID is not a valid connection
		if( it == connections.end() ) return;

		// Initialize structure for errors
		websocketpp::lib::error_code ec;
		
		// Request to send a message
		this->endpoint.send( it->second->getHandle(), message, websocketpp::frame::opcode::text, ec );

		// if( ec ) { std::cout << ec.message() << std::endl; }
		// else { std::cout << "succ" << std::endl; }
	}
}

void WebSocket::close( unsigned short cid ) {
	// Verify the connection ID is in the valid range
	if( cid < this->cid ) {
		// Search for the connection in the map
		map<unsigned short, WSConnection::ptr>::iterator it = connections.find( cid );

		// Exit if the ID is not a valid connection
		if( it == connections.end() ) return;

		// Initialize structure for errors
		websocketpp::lib::error_code ec;
		
		// Request to send a message
		this->endpoint.close( it->second->getHandle(), websocketpp::close::status::force_tcp_drop, "", ec );

		// if( ec ) { std::cout << ec.message() << std::endl; }
		// else { std::cout << "succ" << std::endl; }
	}
}

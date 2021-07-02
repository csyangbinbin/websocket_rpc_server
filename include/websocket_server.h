#ifndef __WEBSOCKET_SERVER_INCLUDE__
#define __WEBSOCKET_SERVER_INCLUDE__
#include <vector>
#include <thread>
#include <uwebsockets/App.h>
#include <jsonrpccpp/server/abstractserverconnector.h>
struct PerSocketData {
	/* Fill with user data */
};

class WebSocketServer : public jsonrpc::AbstractServerConnector {
public:
	WebSocketServer(const std::string& pattern="/*" , int listen_port = 9000);
	virtual~WebSocketServer();
    virtual bool StartListening();
    virtual bool StopListening();
    bool virtual SendResponse(const std::string& response, void* addInfo = NULL) ;
public:
	uWS::App* globalApp;
	std::string pattern_;
	int listen_port_; 
	std::vector<std::thread*> threads;
	std::vector<struct us_listen_socket_t*>  global_listen_sockets;
	
};


#endif

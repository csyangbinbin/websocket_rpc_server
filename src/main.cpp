#include <stdio.h>
#include "include/websocket_server.h"
#include "include/MyStubServer.h"

int main() {
	WebSocketServer wsserver;
	  MyStubServer s(wsserver,JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
	  s.StartListening();
	  cout << "Hit enter to stop the server" << endl;
	  getchar();
	
	  s.StopListening();
	
  return 0;
}

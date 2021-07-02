#include "include/websocket_server.h"
#include <string>
#include <mutex>
std::mutex stdoutMutex;
WebSocketServer::WebSocketServer(const std::string& pattern/* = "/*"*/, int listen_port /*= 9000*/):
	globalApp(NULL),
    pattern_(pattern),
    listen_port_(listen_port){
}
WebSocketServer::~WebSocketServer() {
}

 bool WebSocketServer::StartListening() {
     if (threads.empty() == false)
         return false;

     threads = std::vector<std::thread*>(std::thread::hardware_concurrency());
     std::transform(threads.begin(), threads.end(), threads.begin(), [this](std::thread*/*t*/) {
         return new std::thread([this]() {
             uWS::App().ws<PerSocketData>(pattern_, {
                 .compression = uWS::SHARED_COMPRESSOR,
                 .maxPayloadLength = 16 * 1024 * 1024,
                 .maxBackpressure = 1 * 1024 * 1024,
                 .closeOnBackpressureLimit = false,
                 .resetIdleTimeoutOnSend = false,
                 .sendPingsAutomatically = true,

                 .open = [](auto* ws) {
                /*    auto addr = ws->getRemoteAddressAsText();
                    std::cout << "getRemoteAddress:" << addr;*/
                 },
                 .message = [this](auto* ws, std::string_view message, uWS::OpCode opCode) {
                     if (opCode != uWS::OpCode::TEXT)
                         return; 
                    this->OnRequest(std::string(message.begin() , message.end()), reinterpret_cast<void*>(ws));
                 },
                 .close = [](auto* ws, int code, std::string_view message) {
                     /* You may access ws->getUserData() here */
                 }
                 }).listen(listen_port_, [this](auto* listen_socket) {
                     stdoutMutex.lock();
                     if (listen_socket) {
                         global_listen_sockets.push_back(listen_socket);
                         std::cout << "WS Thread: " << std::this_thread::get_id() << " listening on port " << listen_port_ << std::endl;
                     }
                     else {
                         std::cout << "WS Thread " << std::this_thread::get_id() << " failed to listen on port "<< listen_port_ << std::endl;
                     }
                     stdoutMutex.unlock();
                     }).run();
             ///
             });
         }); 
         return true; 
}
 bool WebSocketServer::StopListening() {
     return true; 
}
 bool WebSocketServer::SendResponse(const std::string& response, void* addInfo ) {
     uWS::WebSocket<false, true, PerSocketData>* ws = reinterpret_cast<uWS::WebSocket<false, true, PerSocketData>*>(addInfo); 
     if (ws == NULL)
         return false; 
     ws->send(response, uWS::OpCode::TEXT ,false);
     return true; 
}

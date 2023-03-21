#include "server_socket.h"
#include "socket_exception.h"

// Socket initialized for server ia create, then bind and followed by listen
ServerSocket::ServerSocket(int port) {
	if(!create())
		throw SocketException("couldnt create server socket");
	if(!bind(port))
		throw SocketException("couldnt bind to port");
	if(!listen())
		throw SocketException("couldnt listen to socket");
}

ServerSocket::~ServerSocket() {
	close();
}

// wrapper for send
bool ServerSocket::send(char* s) {
	if(!Socket::send(s))
		throw SocketException("send failed");
	return true;
}
// wrapper for receive
int ServerSocket::recv(char* buffer, int length) {
	if(Socket::recv(buffer, length)<=0)
		throw SocketException("recv failed");
	return 0;
}


void ServerSocket::accept ( ServerSocket& sock )
{
  if (!Socket::accept(sock )) {
      throw SocketException ( "Could not accept socket." );
    }
}
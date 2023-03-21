#include "client_socket.h"
#include "socket_exception.h"


ClientSocket::ClientSocket ( char* host, int port ) {
  if(!create())
      throw SocketException ( "Could not create client socket." );

  if(!connect(host, port))
      throw SocketException ( "Could not bind to port." );
}


bool ClientSocket::send(char* s) {
  if(!Socket::send(s))
    throw SocketException("send failed");
  return true;
}

int ClientSocket::recv(char* buffer, int length) {
  if(Socket::recv(buffer, length)<=0)
    throw SocketException("recv failed");
  return 0;
}
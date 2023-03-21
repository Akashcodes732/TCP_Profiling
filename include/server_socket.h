#ifndef SERVER_SOCKET_H_
#define SERVER_SOCKET_H_
#include "socket.h"

class ServerSocket : private Socket {
public:
	ServerSocket(){};
	ServerSocket(int port);
	virtual ~ServerSocket();
	
	bool send(char* s);
	int recv(char* buffer, int length);

	void accept ( ServerSocket& );
};
#endif //SERVER_SOCKET_H_
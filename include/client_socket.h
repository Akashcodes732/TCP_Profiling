#ifndef CLIENT_SOCKET_H_
#define CLIENT_SOCKET_H_
#include "socket.h"

class ClientSocket : private Socket {
public:
	ClientSocket(char* ip, int port);
	virtual ~ClientSocket(){};

	bool send(char* s);
	int recv(char* buffer, int length);
};
#endif //CLIENT_SOCKET_H_
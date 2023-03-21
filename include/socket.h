#ifndef SOCKET_H_
#define SOCKET_H_
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
	Simply a socket class that is extendible to make both client or server or alternate sockets
*/
class Socket {
public:
	//default constructor: socket_fd will be initialized to -1.
	Socket();
	Socket(int sd);

	bool create();
	
	// server initialization
	bool listen();
	bool bind(int port);
	bool accept(Socket&);

	// client initialization
	bool connect(const char* host, int port);
	
	// data transfer
	bool send(char* s);
	int recv(char* buffer, int length);
	void close();
	void doServerTask();
	void doClientTask();
private:
	int socket_fd;
	sockaddr_in address;

};
#endif //SOCKET_H_
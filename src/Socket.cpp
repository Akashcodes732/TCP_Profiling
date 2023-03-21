#include "socket.h"
#include "socket_exception.h"
#include <stdio.h>
#include <iostream>

Socket::Socket():socket_fd(-1) {
	memset(&address, 0, sizeof(address));
}
Socket::Socket(int sd):socket_fd(sd) {
	memset(&address, 0, sizeof(address));
}
bool Socket::create() {
	// Creating socket file descriptor
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd<0)
		return false;
	
	int opt=1;
	// Forcefully attaching socket to the port 8080
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		return false;
	}
	return true;
}
// binds the socket onto the port
bool Socket::bind(int port) {
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    // Forcefully attaching socket to the port 8080
    if (::bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return false;
    }
    return true;
}
// listen for any connection requests on socket
bool Socket::listen() {
	if (::listen(socket_fd, 3) < 0) {
		perror("listen");
		return false;
	}
	return true;
}

// Accepts a connect request and assigns the new socket with fd so it can send and receives messages on that socket.
bool Socket::accept(Socket& new_socket) {
	int addrlen = sizeof(address);
	if ((new_socket.socket_fd = ::accept(socket_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		return false;
	}
	return true;
}

bool Socket::connect(const char* host, int port) {
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, host, &address.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return false;
	}
	int status;
	if ((status = ::connect(socket_fd, (struct sockaddr*)&address, sizeof(address))) < 0) {
		printf("\nConnection Failed \n");
		return false;
	}
	return true;
}
// send message via socket by writing on socket's fd
bool Socket::send(char* s) {
	int status = ::send(socket_fd, s, strlen(s), 0);
	printf("message sent: %s\n", s);
	if ( status == -1 )
    {
      return false;
    }
  else
    {
      return true;
    }
}

// read message via socket by reading from socket's fd
int Socket::recv(char* buffer, int length) {
	int valread = ::read(socket_fd, buffer, length);
	printf("message received:%s\n", buffer);
}

void Socket::close() {
	::close(socket_fd);
}
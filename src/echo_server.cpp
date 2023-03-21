#include <iostream>
#include "server_socket.h"
#include "socket_exception.h"
#define MAX_MSG_SIZE 1024
#define PREFERRED_PORT 8080
int main() {
	try {
		ServerSocket server(PREFERRED_PORT);
		ServerSocket new_sock;
		server.accept(new_sock);
		char buffer[MAX_MSG_SIZE];
		int valread;
		do {
			memset(buffer, 0, MAX_MSG_SIZE);
	    new_sock.recv(buffer, MAX_MSG_SIZE);
	    new_sock.send(buffer); // could further be optimized by multithreading. This function could be run in a different thread and detached
    } while(strcmp(buffer, "exit")!=0 && strcmp(buffer, "")!=0); // continue echoing till "exit" or empty message is received
	}
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.what() << "\nExiting.\n";
    }
	return 0;
}
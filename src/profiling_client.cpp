#include "profiling_client_socket.h"
#include "socket_exception.h"
#include <iostream>
#define PREFERRED_PORT 8080

// can be invoked w/o commandline arguments or with 1 to 3 arguments (message count, message length, IP address)
int main(int argc, char** argv) {
	char *ip = "127.0.0.1";
	int msg_count=3, msg_length=20;
	if(argc > 1)
		msg_count=atoi(argv[1]);
	if(argc>2)
		msg_length=atoi(argv[2]);
	if(argc>3)
		ip = argv[3];
	try {
		ProfilingClientSocket pclient(ip, PREFERRED_PORT, msg_count, msg_length);
		pclient.ProfileMessages();
	} catch(SocketException e) {
		std::cout << "Exception was caught:" << e.what() << "\nExiting.\n";
	}
	return 0;
}

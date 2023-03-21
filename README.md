# TCP_Profiling

## Run the following two commands to compile for server and client:
1) g++ -pthread -std=c++17 -I./include/ src/ServerSocket.cpp src/Socket.cpp src/echo_server.cpp -o server
2) g++ -pthread -std=c++17 -I./include/ src/ClientSocket.cpp src/Socket.cpp src/profiling_client.cpp src/ProfilingClientSocket.cpp -o client

### To run, first run server then client:
1) ./server
2) ./client


## Additional notes:
1) The format of a message is "<msg*>***********"  here * is a letter of alphabet [a-z], based on index.
	For eg: if msg_count = 4, msg_length=10
		msgs = {"<msga>aaaa",
				"<msgb>bbbb",
				"<msgc>cccc",
				"<msgd>dddd"}
				
2) The client application can be given additional command line arguments
    ./client {message_count} {message_length} {IP_address}
    
    message_count: number of messages between 1-26 (default: 3)
    message_length: length of messages between 10-1024 (default: 20)
    IP_address: IP address string (default: "127.0.0.1")
    
## About the source code:
1) Classes - 
    a) Socket
    b) Socket is inherited by ServerSocket, Client Socket
    c) ClientSocket is inherited by ProfilingClientSocket
    d) Socket exception to raise socket exceptions
2) demo_server.cpp and profiling_client.cpp have the respective server and client main functions.

#ifndef PROFILING_CLIENT_SOCKET_H_
#define PROFILING_CLIENT_SOCKET_H_
#include "client_socket.h"
#include <chrono>
#include <vector>
#include <mutex>
#include <string>

using microsecondsTy = std::chrono::microseconds;


/*
	ProfilingClientSocket is our special type of client socket that can send multiple messages asynchronously.
	It also records some profiling information about the transmission of messages like network delays.
	For each message it shows round trip time, running average of round trip time and a running rate of throughput.
*/
class ProfilingClientSocket : public ClientSocket {
public:
	// Establishes the socket connections. Initialized variables and calls generate_message
	ProfilingClientSocket(char * ip, int port, int msg_count, int msg_length);
	~ProfilingClientSocket(){};

	// thread-safe send and receive functions. Also calculates the different network delays.
	void lock_send(char* s);
	void lock_recv(char* buffer);

	// Creates different threads to send and receive the messages
	void ProfileMessages();

	void generate_messages();

private:
	// Get index of message in msgs vector based on message format
	int get_message_index(char*);

	// helper function to get duration in microseconds since start_time is initialized.
	microsecondsTy time_since_start_time();

	std::vector<std::string> msgs;
	int msg_count, msg_length;					// Count of messages to be send asynchronously and their length. 
	std::mutex send_lock, recv_lock;
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time; 			// start time for reference
	std::vector<microsecondsTy> starts;			// will hold time of sending for each message
	int msg_received_count;						
	uint64_t round_trip_time_total;				// for calculating running average of RTT
};
#endif //PROFILING_CLIENT_SOCKET_H_
#include "profiling_client_socket.h"
#include "socket_exception.h"
#include <thread>
#include <iostream>
#define MAX_MSG_LEN 1024

ProfilingClientSocket::ProfilingClientSocket(char * ip, int port, int msg_count, int msg_length): 
	ClientSocket(ip, port),
	msg_count(msg_count), msg_length(msg_length), round_trip_time_total(0), msg_received_count(0) {
		if(msg_count > 26 || msg_count<=0)
			throw SocketException("count of messages should be between 1 and 26");
		if(msg_length > 1024 || msg_length<=9)
			throw SocketException("length of messages should between 10 and 1024");

		starts = std::vector<microsecondsTy>(msg_count);

		generate_messages();
}
/*
	generates messages array based on message count and length. Current message format in string
	"<msg*>***********"  -  here * is a letter of alphabet [a-z], based on index.
	For eg: if msg_count = 4, msg_length=10
		msgs = {"<msga>aaaa",
				"<msgb>bbbb"
				"<msgc>cccc"
				"<msgd>dddd"}
*/
void ProfilingClientSocket::generate_messages() {
	for(int i=0;i<msg_count;i++) {
		std::string s;
		for(int j=0;j<msg_length;j++)
			s.push_back('a'+i);
		s.replace(0, 6, "<msg*>");
		s[4] = 'a'+i;
		msgs.push_back(s);
	}
}
microsecondsTy ProfilingClientSocket::time_since_start_time() {
	return std::chrono::duration_cast<microsecondsTy>(std::chrono::high_resolution_clock::now() - start_time);
}

int ProfilingClientSocket::get_message_index(char* s) {
	return s[4]-'a';
}

/* thread-safe send function. Also records time before sending
*/
void ProfilingClientSocket::lock_send(char* s) {
	send_lock.lock();
	starts[get_message_index(s)] = time_since_start_time();
	ClientSocket::send(s);
	send_lock.unlock();
}

/* thread-safe received function. It also records the time taken to received back the echo from server.
Also prints round-trip time, running RTT average and running throughput rate. 
*/ 
void ProfilingClientSocket::lock_recv(char* s) {
	char buf[MAX_MSG_LEN];
	recv_lock.lock();
	ClientSocket::recv(buf, msg_length);
	msg_received_count++;
	microsecondsTy round_trip_time = time_since_start_time()-starts[get_message_index(buf)];
	round_trip_time_total += round_trip_time.count();
	std::cout << "Round trip time(microseconds): " << round_trip_time.count() << std::endl;
	std::cout << "Round trip time running average(microseconds): " << round_trip_time_total/msg_received_count << std::endl;
	std::cout << "Throughput running rate (Kilobytes per second): " << msg_received_count*2*msg_length*sizeof(char)*1000/time_since_start_time().count() << std::endl; 
	recv_lock.unlock();
}

void ProfilingClientSocket::ProfileMessages() {
 
    // initialize start time of this program for reference
    start_time = std::chrono::high_resolution_clock::now();

    msg_received_count = 0;

 	// creating threads for sending and receiving messages
    std::thread the_threads[msg_count*2];
    for(int i=0;i<msg_count;i++) {
    	char *msg = new char[msg_length];
    	strcpy(msg, msgs[i].c_str());
	    the_threads[i] = std::thread(&ProfilingClientSocket::lock_send, this, msg);
	    
	    char s[MAX_MSG_LEN] = {0};
	    the_threads[msg_count+i] = std::thread(&ProfilingClientSocket::lock_recv, this, s);
	}
    std::cout << "threads creation done" << std::endl;

    // joining the threads
    for(int i=0;i<msg_count;i++) {
	    the_threads[i].join();
	    the_threads[msg_count+i].join();
	}
    std::cout << "threads joining done" << std::endl;
    
    // print time taken for the transmission and receiving of all messages
    auto total_time = time_since_start_time();
    std::cout << "Total time taken: " << total_time.count() << " microseconds" << std::endl;
    
    // Lets server know before closing connection so it can disconnect as well
    lock_send("exit");
}
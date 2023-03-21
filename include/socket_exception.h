#ifndef SOCKET_EXCEPTION_H_
#define SOCKET_EXCEPTION_H_
#include<string>
class SocketException : public std::exception {
public:
	SocketException(std::string s) :m_s(s) {};
	~SocketException(){};
	std::string what() { return m_s;}
private:
	std::string m_s; // the exemption message

};
#endif //SOCKET_EXCEPTION_H_
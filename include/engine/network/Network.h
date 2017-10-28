#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#include <thread>

#define PORT "9234"
#define MAXDATASIZE 100

class Network {
private:
	bool m_isInit = false;
	int sockfd;
	addrinfo hints, *servinfo;
	int rv;
	int numbytes;
	static const int MAXBUFLEN = 100;
	char buf[MAXBUFLEN];

	bool winInit();
	void winClose();
public:
	Network();
	~Network();
	bool init();

	bool connectIp(std::string ip, std::string port);
	void disconnect();

	void close();
};

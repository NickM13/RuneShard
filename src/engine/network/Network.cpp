#include "engine\network\Network.h"
#include <iostream>

Network::Network() {
	m_isInit = false;
}

Network::~Network() {
	close();
}

// Windows init
bool Network::winInit() {
	WSADATA wsaData;

	// MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:
	if(WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		printf("Error: WSAStartup\n");
		return false;
	}
	return true;
}

bool Network::init() {
	if(!m_isInit) {
		if(!winInit()) return false;
		m_isInit = true;
	}
	return true;
}
void *get_in_addr(struct sockaddr *sa)
{
	if(sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
bool Network::connectIp(std::string ip, std::string port = PORT) {
	sockaddr_storage serv_addr;
	socklen_t addr_len = sizeof serv_addr;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	if(getaddrinfo(ip.c_str(), port.c_str(), &hints, &servinfo) == -1) {
		printf("Failed to connect\n");
		return false;
	}

	if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
		printf("Unable to create socket\n");
		return false;
	}
	if(sendto(sockfd, "connect", strlen("connect"), 0, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
		printf("Could not send to address\n");
		return false;
	}

	if((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, (sockaddr *)&serv_addr, &addr_len)) == -1) {
		printf("Timed out\n");
		return false;
	}
	buf[numbytes] = '\0';
	if(strcmp(buf, "accept")) {
		printf("Connection denied\n");
		return false;
	}
	char host[100];
	char service[20];
	getnameinfo(servinfo->ai_addr, servinfo->ai_addrlen, host, sizeof host, service, sizeof service, 0);
	printf("Connection established: %s:%s\n", host, service);

	if(servinfo == NULL) {
		fprintf(stderr, "talker: failed to create socket\n");
		return false;
	}

	freeaddrinfo(servinfo);

	closesocket(sockfd);

	return true;
}

void Network::disconnect() {

}

void Network::winClose() {
	WSACleanup();
}
void Network::close() {
	if(m_isInit) {
		winClose();
	}
}

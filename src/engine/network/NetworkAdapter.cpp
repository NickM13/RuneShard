#include "engine\network\NetworkAdapter.h"

Network *NetworkAdapter::m_network = 0;

bool NetworkAdapter::init() {
	m_network = new Network();
	return m_network->init();
}

void NetworkAdapter::close() {
	delete m_network;
}

bool NetworkAdapter::connectIp(std::string ip, std::string port) {
	if(!m_network->connectIp(ip, port)) {
		printf("Error connecting to ip %s:%s\n", ip.c_str(), port.c_str());
		return false;
	}
	return true;
}

bool NetworkAdapter::disconnect() {
	m_network->disconnect();
	return true;
}

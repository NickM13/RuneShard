#pragma once

#include "Network.h"
#include <thread>

class NetworkAdapter {
private:
	static Network *m_network;
public:
	static bool init();
	static void close();
	static bool connectIp(std::string ip, std::string port = PORT);
	static bool disconnect();
};

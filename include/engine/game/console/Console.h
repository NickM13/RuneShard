#pragma once
#include "engine\utils\Utilities.h"

class MConsole {
public:
	struct ConsoleLine {
		enum MessageType {
			NORMAL = 0,
			WARNING = 1,
			MISUSE = 2
		} type;
		std::string message;
	};
private:
	static std::vector<ConsoleLine> m_consoleLog;
	static std::string m_inputLine;
	static bool m_isOpen;
public:
	static void addLine(ConsoleLine::MessageType type, std::string p_message);
	static void setOpen(bool p_state);
	static bool isOpen();
	static void input();
	static void update();
	static void render();
};

#pragma once
#include "engine\utils\Utilities.h"

class MConsole {
public:
	struct ConsoleLine {
		enum MessageType {
			INPUT = 0,
			NORMAL = 1,
			WARNING = 2,
			MISUSE = 3
		} type;
		std::string message;
	};
private:
	static std::vector<ConsoleLine> m_consoleLog;
	static std::string m_inputLine;
	static bool m_isOpen;
	static Sint32 m_scroll;
	static const Sint8 m_linesVisible = 30;
public:
	static void addLine(ConsoleLine::MessageType type, std::string p_message);
	static void setOpen(bool p_state);
	static bool isOpen();
	static void input();
	static void update();
	static void render();
};

#pragma once
#include "engine\utils\Utilities.h"
#include <map>
#include <strstream>
#include <algorithm>
#include <functional>

struct ChatCommand {
private:
	std::function<bool(std::vector<std::string>)> m_function;
	std::string m_usage;
public:
	ChatCommand(std::function<bool(std::vector<std::string>)> p_function, std::string p_usage);
	void callFunction(std::string p_cmd);
	void printMisuse();
};

class MChatCommand {
private:
	static std::map<std::string, ChatCommand*> m_commands;
public:
	static void addCommand(std::string p_cmdName, ChatCommand* p_chatCmd);
	static void checkCommand(std::string p_command);
};

struct KeyCommand {
private:
	std::function<void()> m_function;
public:
	KeyCommand(std::function<void()> p_function) {
		m_function = p_function;
	}
	void callFunction() {
		m_function();
	}
};
class MKeyCommand {
public:
	struct KeyBind {
		Sint32 keyCode, mods;
	};
private:
	static std::map<std::pair<Sint32, Sint32>, KeyCommand*> m_commands;
public:
	static void addCommand(KeyBind p_keyBind, KeyCommand* p_chatCmd);
	static void checkCommand(KeyBind p_keyBind);
};

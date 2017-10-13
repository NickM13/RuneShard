#include "engine\game\command\Command.h"

#include "engine\game\console\Console.h"
#include <locale>

ChatCommand::ChatCommand(std::function<bool(std::vector<std::string>)> p_function, std::string p_usage, std::string p_description) {
	m_function = p_function;
	m_usage = p_usage;
	m_description = p_description;
}
void ChatCommand::callFunction(std::string p_cmd) {
	std::vector<std::string> args;
	std::stringstream ss(p_cmd);
	std::string arg;
	while(std::getline(ss, arg, ' '))
		args.push_back(arg);
	if(!m_function(args))
		printMisuse();
}
void ChatCommand::printMisuse() {
	MConsole::addLine(MConsole::ConsoleLine::MISUSE, "Error: Command unknown, did you mean '" + m_usage + "'?");
}
std::string ChatCommand::getUsage() const {
	return m_usage;
}
std::string ChatCommand::getDescription() const {
	return m_description;
}

std::map<std::string, ChatCommand*> MChatCommand::m_commands;

void MChatCommand::addCommand(std::string p_cmdName, ChatCommand* p_chatCmd) {
	m_commands.insert({p_cmdName, p_chatCmd});
}
void MChatCommand::checkCommand(std::string p_command) {
	std::locale loc;
	for(Uint32 i = 0; i < p_command.size(); i++) {
		p_command[i] = std::tolower(p_command[i], loc);
	}
	std::string arg0 = p_command.substr(0, p_command.find(' '));
	if(m_commands.find(arg0) != m_commands.end())
		m_commands[arg0]->callFunction(p_command);
	else
		MConsole::addLine(MConsole::ConsoleLine::MISUSE, "Error: Command '" + arg0 + "' unknown");
}
void MChatCommand::help() {
	for(std::pair<std::string, ChatCommand*> cmd : m_commands) {
		MConsole::addLine(MConsole::ConsoleLine::NORMAL, cmd.first + " <" + cmd.second->getUsage() + ">: " + cmd.second->getDescription());
	}
}


std::map<std::pair<Sint32, Sint32>, KeyCommand*> MKeyCommand::m_commands;

void MKeyCommand::addCommand(KeyBind p_keyBind, KeyCommand * p_chatCmd) {
	m_commands.insert({{p_keyBind.keyCode, p_keyBind.mods}, p_chatCmd});
}
void MKeyCommand::checkCommand(MKeyCommand::KeyBind p_keyBind) {
	if(m_commands.find({p_keyBind.keyCode, p_keyBind.mods}) != m_commands.end())
		m_commands[{p_keyBind.keyCode, p_keyBind.mods}]->callFunction();
}

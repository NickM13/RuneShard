#include "engine\game\command\Command.h"

#include "engine\game\console\Console.h"

ChatCommand::ChatCommand(std::function<bool(std::vector<std::string>)> p_function, std::string p_usage) {
	m_function = p_function;
	m_usage = p_usage;
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

std::map<std::string, ChatCommand*> MChatCommand::m_commands;

void MChatCommand::addCommand(std::string p_cmdName, ChatCommand* p_chatCmd) {
	m_commands.insert({p_cmdName, p_chatCmd});
}
void MChatCommand::checkCommand(std::string p_command) {
	std::string arg0 = p_command.substr(0, p_command.find(' '));
	if(m_commands.find(arg0) != m_commands.end())
		m_commands[arg0]->callFunction(p_command);
	else
		MConsole::addLine(MConsole::ConsoleLine::MISUSE, "Error: Command '" + arg0 + "' unknown");
}


std::map<std::pair<Sint32, Sint32>, KeyCommand*> MKeyCommand::m_commands;

void MKeyCommand::addCommand(KeyBind p_keyBind, KeyCommand * p_chatCmd) {
	m_commands.insert({{p_keyBind.keyCode, p_keyBind.mods}, p_chatCmd});
}
void MKeyCommand::checkCommand(MKeyCommand::KeyBind p_keyBind) {
	if(m_commands.find({p_keyBind.keyCode, p_keyBind.mods}) != m_commands.end())
		m_commands[{p_keyBind.keyCode, p_keyBind.mods}]->callFunction();
}

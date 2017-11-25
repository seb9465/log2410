#include "CommandExecutor.h"

CommandExecutor & CommandExecutor::getInstance(void)
{
	static CommandExecutor m_instance;
	return m_instance;
}

void CommandExecutor::addCommand(const std::shared_ptr<AbsCommand>& c)
{
	m_commandList.push_back(c);
}

void CommandExecutor::executeAllCommands(AbsAudioFile& f)
{
	for(auto it = m_commandList.begin(); it != m_commandList.end(); it++)
		(it->get())->execute(f);
}

void CommandExecutor::clearAllCommands(void)
{
	m_commandList.clear();
}
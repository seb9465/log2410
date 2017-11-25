#include "StringFindReplaceCommand.h"
#include "AbsAudioFile.h"

void StringFindReplaceCommand::execute(AbsAudioFile & f)
{
	f.accept(m_visitor);
}
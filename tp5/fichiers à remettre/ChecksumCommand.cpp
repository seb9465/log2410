#include "ChecksumCommand.h"
#include "AbsAudioFile.h"

void ChecksumCommand::execute(AbsAudioFile & f)
{
	f.accept(m_visitor);
}

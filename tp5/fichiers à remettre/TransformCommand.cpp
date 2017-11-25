#include "TransformCommand.h"
#include "MemAudioFile.h"

TransformCommand::TransformCommand(std::shared_ptr<AbsTransform> t, const std::string& outFileName)
	: m_transform(t), m_outFile(std::make_shared<MemAudioFile>(outFileName))
{
}

TransformCommand::TransformCommand(std::shared_ptr<AbsTransform> t, const std::shared_ptr<AbsAudioFile>& outFile)
	: m_transform(t), m_outFile(outFile)
{
}

void TransformCommand::execute(AbsAudioFile & f)
{
	for (auto it = f.begin(); it != f.end(); it++)
		m_transform->transform(it, *getOutFile());
}
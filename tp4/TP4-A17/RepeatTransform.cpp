#include "RepeatTransform.h"

void RepeatTransform::transform(const Chunk_iterator& c, AbsAudioFile& outFile) const
{
	// On repete m_nRepetitions fois le 'Chunk' au 'outFile'.
	for (int i = 0; i < m_nRepetitions; i++)
		outFile.addChunk(c);
}

size_t RepeatTransform::getNRepetitions(void)
{
	return m_nRepetitions;
}


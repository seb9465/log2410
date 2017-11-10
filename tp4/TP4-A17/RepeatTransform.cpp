#include "RepeatTransform.h"

void RepeatTransform::transform(const Chunk_iterator& c, AbsAudioFile& outFile) const {
	// On ajoute m_nRepetitions fois le Chunk au fichier de sortie.

	for (size_t i = 0; i < getNRepetitions(); i++)
		outFile.addChunk(c);
}

size_t RepeatTransform::getNRepetitions(void) const {
	return m_nRepetitions;
}
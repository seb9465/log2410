#include "InvertTransform.h"

// Methode pour appliquer une transformation d'inversion à un Chunk
void InvertTransform::transform(const Chunk_iterator& c, AbsAudioFile& outFile) const
{ 
	int chunkSize = c->size();
	char* tmpChunk = c->get();

	std::vector<char> tmp;
	tmp.resize(chunkSize);

	for (int i = 0; i < chunkSize; i++)
		tmp[i] = tmpChunk[chunkSize - 1 - i];

	Chunk_iterator chunkIterator(outFile, outFile.getNumberChunks());
	*chunkIterator = Chunk(tmp.size(), tmp.data());
	outFile.addChunk(chunkIterator);
}

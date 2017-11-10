#include "InvertTransform.h"

// Methode pour appliquer une transformation d'inversion � un Chunk
void InvertTransform::transform(const Chunk_iterator& c, AbsAudioFile& outFile) const { 
	int chunkSize = c->size();						// Copie de la taille du Chunk.
	char* tmpChunk = c->get();						// Copie des donn�es du Chunk.

	std::vector<char> tmp;					
	tmp.resize(chunkSize);							// Vecteur temporaire de taille �gale au Chunk.

	for (int i = 0; i < chunkSize; i++)
		tmp[i] = tmpChunk[chunkSize - 1 - i];		// Remplissage du vecteur temporaire avec les donn�es en ordre inverse du Chunk.

	Chunk_iterator chunkIterator(outFile, outFile.getNumberChunks());
	*chunkIterator = Chunk(tmp.size(), tmp.data());	// On cr�e un Chunk avec le vecteur contenant les donn�es en ordre inverse.

	outFile.addChunk(chunkIterator);				// Ajout du nouveau Chunk au fichier de sortie.
}
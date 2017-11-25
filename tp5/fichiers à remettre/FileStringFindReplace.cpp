#include <algorithm>

#include "FileStringFindReplace.h"
#include "ChunkIterator.h"
#include "MemAudioFile.h"

FileStringFindReplace::FileStringFindReplace(const std::vector<char>& sOrig, const std::vector<char> & sNew, const std::string & outFileName)
	: m_searchString(sOrig), m_replaceString(sNew), m_outFile(std::make_shared<MemAudioFile>(outFileName))
{
}

FileStringFindReplace::FileStringFindReplace(const std::vector<char>& sOrig, const std::vector<char> & sNew, const std::shared_ptr<AbsAudioFile>& outFile)
	: m_searchString(sOrig), m_replaceString(sNew), m_outFile(outFile)
{
}

FileStringFindReplace * FileStringFindReplace::clone(void)
{
	return new FileStringFindReplace(*this);
}

void FileStringFindReplace::visit(const AudioFile & f)
{
	for (auto it = f.begin(); it != f.end(); it++) {
		Chunk_iterator itFin(*m_outFile, m_outFile->getNumberChunks());
		char* buffer = itFin->get();
		memcpy(buffer, it->get(), itFin->size());
		findReplace(buffer, buffer + f.getChunkSize());
		m_outFile->addChunk(itFin);
	}
}

void FileStringFindReplace::visit(const MemAudioFile & f)
{
	size_t chunkSize = f.getChunkSize();
	size_t nChunks = f.getNumberChunks();
	const char* buf = f.get() + f.getHeaderSize();

	for (auto it = f.begin(); it != f.end(); it++) {
		Chunk_iterator itFin(*m_outFile, m_outFile->getNumberChunks());
		char* buffer = itFin->get();
		memcpy(buffer, it->get(), itFin->size());
		findReplace(buffer, buffer + f.getChunkSize());
		m_outFile->addChunk(itFin);
		buf = buf + chunkSize;
	}
}

void FileStringFindReplace::findReplace(char * p_beg, char * p_end)
{
	auto it = std::search(p_beg, p_end, m_searchString.begin(), m_searchString.end());
	if (it != p_end)
	{
		for (size_t irepl = 0; irepl < m_replaceString.size(); ++irepl)
			*(it + irepl) = m_replaceString[irepl];
	}
}

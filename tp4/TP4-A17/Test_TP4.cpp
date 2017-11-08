
#include "Test_TP4.h"

#include <iostream>
#include <stdexcept>

#include "Test_TP4.h"

bool Test_TP4::CompareFilesEqual(const AbsAudioFile & f1, const AbsAudioFile & f2)
{
	if (f1.getNumberChunks() != f2.getNumberChunks() || f1.getChunkSize() != f2.getChunkSize())
		return false;

	Chunk_const_iterator it1 = f1.begin();
	Chunk_const_iterator it2 = f2.begin();

	while (it1 != f1.end())
	{
		if (*it1 != *it2)
			return false;
		++it1;
		++it2;
	}

	return true;
}

Test_TP4::Test_TP4()
{
	AudioFile audiof1("audiof1.bin");
	if(audiof1.getNumberChunks() == 0)
	{
		Chunk_iterator it(audiof1);
		char* buf = (*it).get();
		size_t chunkSize = audiof1.getChunkSize();
		for (int i1 = 65; i1 < 70; ++i1)
		{
			std::fill(buf, buf + chunkSize, char(i1));
			audiof1.addChunk(it);
		}

		for (int i2 = 0; i2 < chunkSize; ++i2)
			buf[i2] = char(71+i2);
		audiof1.addChunk(it);

		for (int i3 = 120; i3 > 115; --i3)
		{
			std::fill(buf, buf + chunkSize, char(i3));
			audiof1.addChunk(it);
		}
	}
	else if (audiof1.getNumberChunks() != 11)
	{
		throw std::runtime_error("Attention! Le fichier audiof1.bin ne contient pas le nombre attendu de Chunks.");
	}
}

Test_TP4::~Test_TP4()
{
}

void Test_TP4::executeProxyTest()
{
	std::cout << std::endl << std::endl << "------------------------- PROXY -------------------------------" << std::endl << std::endl;
	std::cout << std::endl;

	{
		// Utiliser un proxy pour charger un fichier
		MemAudioFile memFileIn("audiof1.bin");

		// Utiliser un proxy pour reecrire le fichier
		MemAudioFile memFileOut("audiof_proxy.bin");

		for (Chunk_iterator iter = memFileIn.begin(); iter != memFileIn.end(); ++iter)
			memFileOut.addChunk(iter);
	}
	{
		// Verifier l'utilisation du proxy en lecture et ecriture
		AudioFile audiof1("audiof1.bin");
		AudioFile proxyFile("audiof_proxy.bin");
		bool compare = CompareFilesEqual(audiof1, proxyFile);
		std::cout << "PROXY Test 1: " << (compare ? "SUCCES" : "ECHEC") << std::endl;
	}
}

void Test_TP4::executeCompositeTest()
{
	std::cout << std::endl << std::endl << "------------------------- COMPOSITE -------------------------------" << std::endl << std::endl;
	std::cout << std::endl;

	AudioFile audiof1("audiof1.bin");
	AudioFile fileRef("audiof_ref1.bin");
	bool compare = CompareFilesEqual(audiof1, fileRef);
	std::cout << "COMPOSITE Test 1: " << (compare ? "SUCCES" : "ECHEC") << std::endl;

	RepeatTransform rt(2);
	{
		// Appliquer la transformation de repetition seule
		AudioFile audiof_rt("audiof_rt.bin");
		for (Chunk_iterator iter = audiof1.begin(); iter != audiof1.end(); ++iter)
			rt.transform(iter, audiof_rt);
	}
	{
		// Verifier l'application de la transformation de repetition seule
		AudioFile audiof_rt("audiof_rt.bin");
		AudioFile audiof_rt_ref("audiof_rt_ref.bin");
		bool compare = CompareFilesEqual(audiof_rt, audiof_rt_ref);
		std::cout << "COMPOSITE Test 2: " << (compare ? "SUCCES" : "ECHEC") << std::endl;
	}

	InvertTransform invt;
	{
		// Appliquer la transformation d'inversion seule
		AudioFile audiof_inv("audiof_inv.bin");
		for (Chunk_iterator iter = audiof1.begin(); iter != audiof1.end(); ++iter)
			invt.transform(iter, audiof_inv);
	}
	{
		// Verifier l'application de la transformation d'inversion seule
		AudioFile audiof_inv("audiof_inv.bin");
		AudioFile audiof_inv_ref("audiof_inv_ref.bin");
		bool compare = CompareFilesEqual(audiof_inv, audiof_inv_ref);
		std::cout << "COMPOSITE Test 3: " << (compare ? "SUCCES" : "ECHEC") << std::endl;
	}

	CompositeTransform composit1, composit2;
	composit1.addChild(&rt);
	composit1.addChild(&invt);
	composit2.addChild(&invt);
	composit2.addChild(&composit1);
	{
		// Appliquer la transformation composite
		AudioFile audiof_composit("audiof_composit.bin");
		for (Chunk_iterator iter = audiof1.begin(); iter != audiof1.end(); ++iter)
			composit2.transform(iter, audiof_composit);

	}
	{
		// Verifier l'application de la transformation composite
		AudioFile audiof_composit("audiof_composit.bin");
		AudioFile audiof_composit_ref("audiof_composit_ref.bin");
		bool compare = CompareFilesEqual(audiof_composit, audiof_composit_ref);
		std::cout << "COMPOSITE Test 4: " << (compare ? "SUCCES" : "ECHEC") << std::endl;
	}


}

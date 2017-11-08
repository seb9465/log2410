/*****************************************************************************/
//  Test_TP4.h
//  Implementation of the Class Test_TP4
//  Created on:      2015-10-14
//  Modified on:     2016-10-26
//  Original author: El Houcine Boudoukha and Farouk Ouenniche
//  Modification:    Francois Guibault - Adapt to PolyScino
/*****************************************************************************/

#ifndef TEST_TP4_H
#define TEST_TP4_H


#include <memory>
#include <exception>

#include "Chunk.h"
#include "ChunkIterator.h"
#include "CompositeTransform.h"
#include "InvertTransform.h"
#include "RepeatTransform.h"
#include "AudioFile.h"
#include "MemAudioFile.h"

//
// Classe TestTP4
//
// Classe de test pour les elements implementes au TP4
//
class Test_TP4
{
private:
	std::shared_ptr<AbsTransform> racine;
	//std::shared_ptr<AudioFile> audiof1;

protected:
	bool CompareFilesEqual(const AbsAudioFile& f1, const AbsAudioFile& f2);
public:

	//-------------------------------------------
	// Constructeur & Destructeur
	//-------------------------------------------
	Test_TP4();
	~Test_TP4();

	// Tests
	void executeProxyTest();          // Execute les tests sur le Proxy
	void executeCompositeTest();      // Execute les tests sur les composites
};

#endif// TEST_TP4_H

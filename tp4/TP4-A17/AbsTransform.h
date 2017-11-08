///////////////////////////////////////////////////////////
//  AbsTransform.h
//  Implementation of the Class AbsTransform
//  Created on:      13-mar.-2017
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(_HEADER_ABS_TRANSFORM_)
#define _HEADER_ABS_TRANSFORM_

#include <iterator>
#include <vector>

#include "Chunk.h"
#include "AbsAudioFile.h"

class AbsTransform
{
	// Vecteur vide de transformation permettant de retourner des iterateurs valides
	static std::vector<std::shared_ptr<AbsTransform>> m_empty_transforms;

public:
	AbsTransform(void) {};
	virtual ~AbsTransform() {};
	virtual AbsTransform* clone(void) const = 0;

	// Methode pour appliquer une transformation a une partie de fichier audio
	virtual void transform( const Chunk_iterator& c, AbsAudioFile& outFile ) const = 0;

	// Methodes de gestions des enfants
	typedef std::vector<std::shared_ptr<class AbsTransform>>::iterator iterator;
	typedef std::vector<std::shared_ptr<class AbsTransform>>::const_iterator const_iterator;

	virtual const_iterator begin(void) const { return m_empty_transforms.begin(); }
	virtual const_iterator end(void) const { return  m_empty_transforms.end(); }
	virtual iterator begin(void) { return  m_empty_transforms.begin(); }
	virtual iterator end(void) { return  m_empty_transforms.end(); }
	virtual void addChild(const AbsTransform* t) { /* echoue silencieusement */ }
};
#endif // !defined(_HEADER_ABS_TRANSFORM_)

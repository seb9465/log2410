///////////////////////////////////////////////////////////
//  CompositeTransform.h
//  Implementation of the Class CompositeTransform
//  Created on:      13-mar.-2017
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(_HEADER_COMPOSITE_TRANSFORM_)
#define _HEADER_COMPOSITE_TRANSFORM_

#include "AbsTransform.h"

#include <memory>
#include <vector>

class CompositeTransform : public AbsTransform
{
	std::vector<std::shared_ptr<AbsTransform>> m_transforms;

public:
	CompositeTransform(void) {};
	virtual CompositeTransform* clone(void) const;

	// Methode pour appliquer une transformation a une partie de fichier audio
	virtual void transform(const Chunk_iterator& c, AbsAudioFile& outFile) const;

	// Methodes de gestions des enfants
	virtual const_iterator begin(void) const { return m_transforms.begin(); }
	virtual const_iterator end(void) const { return m_transforms.end(); }
	virtual iterator begin(void) { return m_transforms.begin(); }
	virtual iterator end(void) { return m_transforms.end(); }
	virtual void addChild(const AbsTransform* t) { m_transforms.push_back(std::shared_ptr<AbsTransform>(t->clone())); }
};
#endif // !defined(_HEADER_COMPOSITE_TRANSFORM_)

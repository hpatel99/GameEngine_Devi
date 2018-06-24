#ifndef PCSTREE_FORWARD_ITERATOR_H
#define PCSTREE_FORWARD_ITERATOR_H

#include "PCSTreeIterator.h"

class PCSTreeForwardIterator : public PCSTreeIterator
{
public:

	PCSTreeForwardIterator(PCSNode *rootNode);

	virtual PCSNode *First() override;
	virtual PCSNode *Next() override;
	virtual bool IsDone() override;
	virtual PCSNode *CurrentItem() override;

private:

	PCSNode *root;
	PCSNode *current;
};


#endif;
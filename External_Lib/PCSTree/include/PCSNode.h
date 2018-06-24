//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef PCSNODE_H
#define PCSNODE_H

class PCSNode
{
public:
	// Constants for the library
	static const unsigned int NAME_SIZE = 20;
	static const unsigned int MAJOR_VERSION = 2;
	static const unsigned int MINOR_VERSION = 2;

public:
	// Enums
	enum class Code
	{
		SUCCESS,
		FAIL_NULL_PTR,
		FAIL_RETURN_NOT_INITIALIZED,
		DWORD = 0x7fffffff
	};


public:
	// constructor
	PCSNode();

	// copy constructor
	PCSNode(const PCSNode &in);

	// Specialize Constructor
	PCSNode(PCSNode * const pInParent, PCSNode * const pInChild, PCSNode * const pInNextSibling, PCSNode * const pInPrevSibling, const char * const pInName);
	PCSNode(const char * const pInName);

	// destructor
	virtual ~PCSNode();

	// assignment operator
	PCSNode &operator = (const PCSNode &in);

	// accessors
	void SetParent(PCSNode * const pIn);
	void SetChild(PCSNode * const pIn);
	void SetNextSibling(PCSNode * const pIn);
	void SetPrevSibling(PCSNode * const pIn);
	void SetForward(PCSNode * const pIn);
	void SetReverse(PCSNode * const pIn);

	PCSNode *GetParent(void) const;
	PCSNode *GetChild(void) const;
	PCSNode *GetNextSibling(void) const;
	PCSNode *GetPrevSibling(void) const;
	PCSNode *GetForward(void) const;
	PCSNode *GetReverse(void) const;


	// name
	Code SetName(const char * const pInName);
	Code GetName(char * const pOutBuffer, unsigned int sizeOutBuffer) const;

	// print
	void PrintNode() const;
	void PrintChildren() const;
	void PrintSiblings() const;

	// get number of children/siblings
	int GetNumSiblings() const;
	int GetNumChildren() const;

private:
	PCSNode *pParent;
	PCSNode *pChild;
	PCSNode *pNextSibling;
	PCSNode *pPrevSibling;
	PCSNode *pForward;
	PCSNode *pReverse;

	char     pName[PCSNode::NAME_SIZE];
};


#endif

// ---  End of File ---------------

//----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------
// UnitTest v.2.1.0
//          v.2.1.1  - fixed C5038 warning
//			v.2.5
//---------------------------------------------------------------------------- 

#include "UnitTest.h"

Test::Test(const char * pTestName)
	:UnitSLink()
{
	// initialized data
	this->pName = pTestName;
	this->testFunc = this;

	// register it
	TestRegistry::AddTest(this);

}

// ---  End of File ---------------

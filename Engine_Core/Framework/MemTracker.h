//----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------
// MemTracker v.2.1.0
//            v.2.2 - print to console
//			  v.2.5
//---------------------------------------------------------------------------- 

#ifndef MEM_TRACKER_H
#define MEM_TRACKER_H

// ---------------------------------------------------------------------------
// One instructions to rule them all:
//
//   To Enable: 
//             #define MEM_TRACKER_ENABLED
//   To Disable: 
//             comment out #define MEM_TRACKER_ENABLED
//
//   (1) Project Settings:
//      You need to set your project settings
//          Character Set -> Use Multi-Byte Character Set
//
//      Include MemTracker.h to every file:
//           Change your project settings
//               Go to C / C++ tab
//               Go to Advanced
//                      set Forced Include : MemTracker.h
//               This will add this file automagically to all files (great!)
//
//   (2) Modify main.cpp properties:
//      Add MemTrackerMain.h to the first line of main.cpp not the function
//          Has to be the first line of main.cpp 
//               To check static classes/allocations
//               This header will initialize memory tracking as well
//          To accomplish this 
//               set Forced Include on main.cpp: MemTrackerMain.h not MemTracker.h 
//
//   (3) Linker changes
//		    main.cpp has to be first in the linker
//          Reorder manually .vcxproj to insure that this is true
//               Edit the text file .vcxproj 
//
//  Placement new changes:
//      Due to trickery of the new macros... placement new was affected
//          Placement new can be used, but needs to go through a macro instead
//          Memory tracking doesn't affect dynamic allocations
//               Traditional:
//                   new(Addr) Class(args...);
//                   new(buffer) Dog(5,4);
//               New way:
//                   placement_new(WHERE, TYPE, ...); 
//                   placement_new(Addr, Class, args...);
//                   placement_new(buffer, Dog, 5,4);
//
// ---------------------------------------------------------------------------

// Comment out this line to turn off memory tracking
//#define MEM_TRACKER_ENABLED

// General includes
#include <assert.h>
#include <stdio.h>

// Windows.h include
// many warnings - need to wrap for Wall warnings
	#pragma warning( push )
	#pragma warning( disable : 4820 )
	#pragma warning( disable : 4668 )
	#include <Windows.h>
	#pragma warning( pop ) 

// Printing buffer size
#define MemTraceBuffSize 256

// Singleton helper class
class MemTrace
{
public:
	// displays a printf to the output window
	static void out(char* fmt, ...)
	{
		MemTrace *pTrace = MemTrace::privGetInstance();
		assert(pTrace);

		va_list args;
		va_start(args, fmt);

		vsprintf_s(pTrace->privBuff, MemTraceBuffSize, fmt, args);
		OutputDebugString(pTrace->privBuff);

		va_end(args);
	}

	// Big four
	MemTrace() = default;
	MemTrace(const MemTrace &) = default;
	MemTrace & operator = (const MemTrace &) = default;
	~MemTrace() = default;

private:
	static MemTrace *privGetInstance()
	{
		// This is where its actually stored (BSS section)
		static MemTrace helper;
		return &helper;
	}
	char privBuff[MemTraceBuffSize];
};

// Placement new - Macro Trick
template<typename T, typename... Ts>
inline T * _MemTrackerPlacement(void * Where, Ts... args)
{
	return new(Where) T(args...);
}

// Need to use this if MemTracking is enabled
#define placement_new(WHERE, TYPE, ...) _MemTrackerPlacement<TYPE>(WHERE, __VA_ARGS__)

#if defined(_DEBUG) && defined(MEM_TRACKER_ENABLED)
	#define _CRTDBG_MAP_ALLOC  
	#include <stdlib.h>  
	#include <crtdbg.h>  
	#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#pragma warning( push )
#pragma warning( disable : 4820 )
#pragma warning( disable : 4577 )
#pragma warning( disable : 4987 )
	#include <new>
#pragma warning( pop )
#endif


#ifdef MEM_TRACKER_ENABLED

	#ifdef _DEBUG

		#define MEM_TRACKER_PROCESS_END	int _leakCount = _CrtDumpMemoryLeaks(); \
										MemTrace::out("\n"); \
										MemTrace::out("--------------------------------\n"); \
										printf("\n"); \
										printf("--------------------------------\n"); \
										if (_leakCount) { \
										MemTrace::out(">>> Memory Tracking: fail <<<<<<\n"); \
										printf(">>> Memory Tracking: fail <<<<<<\n"); }\
										else {\
										MemTrace::out("    Memory Tracking: passed \n"); \
										printf("    Memory Tracking: passed \n"); }\
										MemTrace::out("--------------------------------\n"); \
										MemTrace::out("    Memory Tracking: end()      \n"); \
										MemTrace::out("--------------------------------\n"); \
										printf("--------------------------------\n"); \
										printf("    Memory Tracking: end()      \n"); \
										printf("--------------------------------\n"); \
										printf("\n"); 

		#define MEM_TRACKER_PROCESS		MemTrace::out("--------------------------------\n"); \
										MemTrace::out("    Memory Tracking: start()    \n"); \
										MemTrace::out("--------------------------------\n"); \
										printf("--------------------------------\n"); \
										printf("    Memory Tracking: start()    \n"); \
										printf("--------------------------------\n"); 
									

	#else
		#define MEM_TRACKER_PROCESS
		#define MEM_TRACKER_END 
	#endif

#else
	#define MEM_TRACKER_PROCESS
	#define MEM_TRACKER_END
#endif

// Note: MemTrackerMain.h
//        Has to be the first line of main.cpp not main()
//		  main.cpp has to be first in link in project
//        reorder manually .vcxproj to insure that this is true

#if defined(_DEBUG) && defined(MEM_TRACKER_ENABLED)

	#define MEM_TRACKER_BEGIN \
	static struct _StaticMem \
	{ \
		 _StaticMem()	{ MEM_TRACKER_PROCESS } \
		~_StaticMem()	{ MEM_TRACKER_PROCESS_END } \
	} _StaticMemInst;

#else

	#define MEM_TRACKER_BEGIN

#endif

#endif

// ---  End of File ---------------

#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H

/*
 * class Timer
 * Measures real durations of time in terms of Time.
 *
 * The Timer interface you see here owes itself to Matlab.
 * You only measure segements of time with a Timer.  Use tic() to
 * mark the beginning of the segment.  Use toc() to mark the end.
 *
 * toc() always returns the amount of time that has elapsed since tic()
 * was called.  If you never call tic() on your Timer then toc() will
 * return @link Time::Time() zero @endlink.
 *
 *
 * Example
 *
 *    #include "Timer.h"
 *
 *    // Create a Timer.
 *    Timer timer;
 *
 *    // Mark our begin time.
 *    timer.tic();
 *
 *    // Do something for a while.
 *    ...
 *
 *    // Measure how much time has gone by since we called tic().
 *    const Time elapsedTime = timer.toc();
 *
 *
 */

 //---------------------------------------------------------------------------
 // HEADER FILES:
 //---------------------------------------------------------------------------

#include "Time.h"

//---------------------------------------------------------------------------
// TEMPLATE DECLARATION:
//---------------------------------------------------------------------------

class Timer
{
public:
	//-----------------------------------------------------------------
	// Constructors / Destructors
	//-----------------------------------------------------------------

	/* Creates a Timer for the platform you are compiling on. */
	Timer();
	Timer(const Timer &) = delete;
	Timer & operator = (const Timer &) = delete;
	~Timer();

	//-----------------------------------------------------------------
	// Timing Methods
	//-----------------------------------------------------------------

	/*
	* Marks the moment in time that toc() will get measured against.
	* Call tic() to mark the beginning of the segment of time that
	* you want to measure.
	*/
	void Tic();

	/*
	* return: The duration of Time that has elapsed since tic() was
	* called.  Returns Time::Time() zero if tic() has
	* never been called on this Timer.
	*/
	const Time Toc() const;


private:
	// static method
	static const Time privGetSystemTime();

	// Data
	Time privTicMark;
};


#endif   // Timer_h


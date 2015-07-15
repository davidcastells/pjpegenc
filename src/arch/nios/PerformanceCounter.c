/*
 * PerformanceCounter.cpp
 *
 *  Created on: 21/12/2012
 *      Author: dcr
 */

#include "PerformanceCounter.h"

#include <io.h>

void perfCounter(uint64 *p64)
{
//    static volatile uint64* pCounter; //  = (uint64*) PERFORMANCECOUNTER_0_BASE;

    //uint64 val64;
    int* pCounter32 = (int*) p64;

    pCounter32[0] = IORD(PERFORMANCECOUNTER_0_BASE, 0);
    pCounter32[1] = IORD(PERFORMANCECOUNTER_0_BASE, 1);

    //return val64;
}


double secondsBetweenLaps(uint64 t0, uint64 tf)
{
	uint64 diff = tf-t0;
	double ddiff = (double) diff;

	if (PERFORMANCE_COUNTER_FREQ == 0)
		return 0;

	double tdif = ddiff / PERFORMANCE_COUNTER_FREQ;

	return tdif;
}

void delay(double seconds)
{
	uint64 t0, tf;

	perfCounter(&t0);

	do
	{
		perfCounter(&tf);
	} while (secondsBetweenLaps(t0, tf) < seconds);
}


/*
void PerformanceCounter_PerformanceCounter(PerformanceCounter* this)
{
	PerformanceCounter_start();
}

void PerformanceCounter_start(PerformanceCounter* this)
{
	this->t0 = perfCounter();
}

void PerformanceCounter_stop(PerformanceCounter* this)
{
	this->tf = perfCounter();
}

double PerformanceCounter_ellapsedSeconds(PerformanceCounter* this)
{
	return ::secondsBetweenLaps(this->t0, this->tf);
}
*/

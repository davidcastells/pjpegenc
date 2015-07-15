#ifndef PERFORMANCECOUNTER_H_
#define PERFORMANCECOUNTER_H_

#include "system.h"

#include <io.h>

#ifndef INT64_DEFINED
typedef long long int64;
typedef unsigned long long uint64;
#define INT64_DEFINED
#endif

#define PERFORMANCE_COUNTER_FREQ	50000000.0

/**
 * Returns the high performance (64bit) counter value
 * It contains the clock cycles from the system initialization
 *
 * @return the number of clocks (50Mhz) from initialization
 */
/*extern  inline __attribute__((always_inline)) */


void perfCounter(uint64 * p64);

double secondsBetweenLaps(uint64 t0, uint64 tf);

/*
typedef struct _PerformanceCounter
{
	uint64 t0;
	uint64 tf;
} PerformanceCounter;



void PerformanceCounter_PerformanceCounter(PerformanceCounter* this);
void PerformanceCounter_start(PerformanceCounter* this);
void PerformanceCounter_stop(PerformanceCounter* this);
double PerformanceCounter_ellapsedSeconds(PerformanceCounter* this);
*/

#endif /*PERFORMANCECOUNTER_H_*/

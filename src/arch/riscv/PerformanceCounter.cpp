/*
 * PerformanceCounter.cpp
 *
 *  Created on: 21/1/2025
 *      Author: dcr
 */

#include "PerformanceCounter.h"

#include <io.h>

void perfCounter(uint64 *p64)
{
// Read the TIME CSR using assembly instruction
  register uint64_t time_high asm("t0");
  register uint64_t time_low asm("t1");

  asm volatile("csrr %0, time" : "=r"(time_high)); 
  asm volatile("csrr %0, timeh" : "=r"(time_low));

  // Combine high and low 32-bit parts into a 64-bit value
  *p64 = (uint64_t)time_high << 32 | time_low;
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



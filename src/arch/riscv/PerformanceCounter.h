#ifndef PERFORMANCECOUNTER_H_
#define PERFORMANCECOUNTER_H_

#include "system.h"

#include <io.h>
#include <stdint.h>

#define uint64 uint64_t


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


#endif /*PERFORMANCECOUNTER_H_*/

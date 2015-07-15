/**
 * 
 * Copyright (C) 2015, David Castells-Rufas <david.castells@uab.es>, CEPHIS, Universitat Autonoma de Barcelona  
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <windows.h>

#include "PerformanceCounter.h"

double freq;
int64 start;

void sec_init(void)
{
	LARGE_INTEGER lFreq, lCnt;
	QueryPerformanceFrequency(&lFreq);
	freq = (double)lFreq.LowPart;
	QueryPerformanceCounter(&lCnt);
	start = lCnt.LowPart;
}
/* return number of seconds since sec_init was called with
** a gross amount of detail
*/
double sec(void)
{
	LARGE_INTEGER lCnt;
	int64 tcnt;
	QueryPerformanceCounter(&lCnt);
 	tcnt = lCnt.LowPart - start;
 	return ((double)tcnt) / freq;
}


void perfCounter(uint64 * p64)
{
    LARGE_INTEGER lCnt;
    QueryPerformanceCounter(&lCnt);
    *p64 = lCnt.QuadPart;
}

double secondsBetweenLaps(uint64 t0, uint64 tf)
{
    uint64 diff = tf - t0;
    LARGE_INTEGER lFreq;
    QueryPerformanceFrequency(&lFreq);
    
    double secs = (double) diff / (double) lFreq.QuadPart;
    
    return secs;
}
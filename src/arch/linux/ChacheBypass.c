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
#include "CacheBypass.h"

void CacheBypassRead(int* ptr, int size)
{
	int i;
	for (i=0; i < size/4; i++)
		CacheBypassReadInt(&ptr[i]);

	if (size % 4 != 0)
		CacheBypassReadInt(&ptr[i]);
}

void CacheBypassWrite(int* ptr, int size)
{
	int i;
	for (i=0; i < size/4; i++)
		CacheBypassWriteInt(&ptr[i], ptr[i]);

	size = size % 4;

	if (size)
	{
		char* pb = (char*) &ptr[i];

		for (i=0; i < size; i++)
			CacheBypassWriteByte(&pb[i], pb[i]);
	}
}



int CacheBypassReadInt(int* ptr)
{
	//*ptr = IORD(ptr, 0);	// read from memory and update cache

	return *ptr;
}

int CacheBypassReadByte(char* ptr)
{
	//*ptr = IORD_8DIRECT(ptr, 0);	// read from memory and update cache

	return *ptr;
}

void CacheBypassWriteInt(int* ptr, int v)
{
	*ptr = v;				// write cache
	//IOWR(ptr, 0, (v));
}

void CacheBypassWriteByte(char* ptr, char v)
{
	*ptr = v;				// write cache
	//IOWR_8DIRECT(ptr, 0, (v));
}

void CacheBypassWriteMemcpy(int* dst, int* src, int size)
{
	int i, v;
	for (i=0; i < size/4; i++)
	{
		v = src[i];
                dst[i] = v;
		//IOWR(&dst[i], 0, (v));
	}

	if (size % 4 != 0)
	{
		v = src[i];
                dst[i] = v;
		//IOWR(&dst[i], 0, (v));
	}
}

void CacheBypassReadMemcpy(int* dst, int* src, int size)
{
	int i, v;
	for (i=0; i < size/4; i++)
	{
		//v = IORD(&src[i], 0);
            v = src[i];
            dst[i] = v;
	}

	if (size % 4 != 0)
	{
		//v = IORD(&src[i], 0);
            v = src[i];
            dst[i] = v;
	}
}

void CacheBypassBothMemcpy(int* dst, int* src, int size)
{
	int i, v;
	for (i=0; i < size/4; i++)
	{
		//v = IORD(&src[i], 0);
            v = src[i];
            //IOWR(&dst[i], 0, (v));
		dst[i] = v;
	}

	if (size % 4 != 0)
	{
		//v = IORD(&src[i], 0);
            v = src[i];
            //IOWR(&dst[i], 0, (v));
		dst[i] = v;
	}
}


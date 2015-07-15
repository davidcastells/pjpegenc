#include "CacheBypass.h"

#include <nios2.h>
#include <io.h>

#define ALT_FLUSH_DATA_NO_WRITEBACK(i) \
  __asm__ volatile ("initda (%0)" :: "r" (i));

void CacheBypassRead(int* ptr, int size)
{
	int i;
	for (i=0; i < size/4; i++)
		ptr[i] = IORD(&ptr[i], 0);

	size = size % 4;

	if (size)
	{
		char* pb = (char*) &ptr[i];

		for (i=0; i < size; i++)
			pb[i] = IORD_8DIRECT(&pb[i], 0);
	}

}

void CacheBypassWrite(int* ptr, int size)
{
	int i;
	for (i=0; i < size/4; i++)
		IOWR(&ptr[i], 0, ptr[i]);

	size = size % 4;

	if (size)
	{
		char* pb = (char*) &ptr[i];

		for (i=0; i < size; i++)
			IOWR_8DIRECT(&pb[i], 0, pb[i]);
	}

	alt_dcache_flush_no_writeback(ptr, size);
}



int CacheBypassReadInt(int* ptr)
{
	register int v;

	ALT_FLUSH_DATA_NO_WRITEBACK(ptr);
	v = IORD(ptr, 0);	// read from memory and update cache

	//*ptr = v;

	return v;
}

int CacheBypassReadByte(char* ptr)
{
	int v;
	ALT_FLUSH_DATA_NO_WRITEBACK(ptr);
	v = IORD_8DIRECT(ptr, 0);	// read from memory and update cache
	//*ptr = v;

	return v;
}

void CacheBypassWriteInt(int* ptr, int v)
{
	ALT_FLUSH_DATA_NO_WRITEBACK(ptr);

	//*ptr = v;				// write cache
	IOWR(ptr, 0, (v));
}

void CacheBypassWriteByte(char* ptr, char v)
{
	ALT_FLUSH_DATA_NO_WRITEBACK(ptr);

	//*ptr = v;				// write cache
	IOWR_8DIRECT(ptr, 0, (v));
}

void CacheBypassWriteMemcpy(int* dst, int* src, int size)
{
	int i, v;
	for (i=0; i < size/4; i++)
	{
		v = src[i];
		IOWR(&dst[i], 0, (v));
	}

	if (size % 4 != 0)
	{
		v = src[i];
		IOWR(&dst[i], 0, (v));
	}
}

void CacheBypassReadMemcpy(int* dst, int* src, int size)
{
	int i, v;
	for (i=0; i < size/4; i++)
	{
		v = IORD(&src[i], 0);
		dst[i] = v;
	}

	if (size % 4 != 0)
	{
		v = IORD(&src[i], 0);
		dst[i] = v;
	}
}

void CacheBypassBothMemcpy(int* dst, int* src, int size)
{
	int i, v;
	for (i=0; i < size/4; i++)
	{
		v = IORD(&src[i], 0);
		IOWR(&dst[i], 0, (v));
		dst[i] = v;
	}

	if (size % 4 != 0)
	{
		v = IORD(&src[i], 0);
		IOWR(&dst[i], 0, (v));
		dst[i] = v;
	}
}


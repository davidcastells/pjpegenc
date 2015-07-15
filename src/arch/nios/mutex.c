
#include "mutex.h"

#include "system.h"

#include <io.h>
#include <nios2.h>

void busyLoop(int pn);

void mutexAcquire()
{
	register int v;
	int c = 20;

loop_aquire:

	v = IORD(MUTEXAVALONSLAVE_0_BASE, 0);

	if (v) //  == 1) @todo check that maybe the concatenation at the JHDL level is done in the wrong order
	{
		busyLoop((c>0)?c--:c);
		goto loop_aquire;
	}
}


void mutexRelease()
{
	register int cpuid;
	NIOS2_READ_CPUID(cpuid);

	IOWR(MUTEXAVALONSLAVE_0_BASE, 0, cpuid);
}

int mutexState()
{
	int v = IORD(MUTEXAVALONSLAVE_0_BASE, 0);

	return v;
}


void busyLoop(int pn)
{
	register int i;
	register int n = pn;

	for (i=0; i<n; i++)
	{
		__asm("nop");
	}
}

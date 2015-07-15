#include "Debug.h"

char MPI_Debug[0x400*4];
int MPI_DebugCount = 0;

void MPI_DebugInit()
{
    CacheBypassWriteInt(&MPI_DebugCount, 0);
}

void MPI_AddDebugLine(char code, int v)
{
	CacheBypassReadInt(&MPI_DebugCount);

//	CacheBypassWriteByte(&MPI_Debug[MPI_DebugCount], c);

	MPI_Debug[MPI_DebugCount] = '0' + mpi_rank();
	MPI_Debug[MPI_DebugCount+1] = code;
	MPI_Debug[MPI_DebugCount+2] =  '0' + v;
	MPI_Debug[MPI_DebugCount+3] = '\n';

	CacheBypassWrite((int*) &MPI_Debug[MPI_DebugCount], 4);
	/*
	CacheBypassWriteByte(&MPI_Debug[MPI_DebugCount],  '0' + mpi_rank());
	CacheBypassWriteByte(&MPI_Debug[MPI_DebugCount+1], code);
	CacheBypassWriteByte(&MPI_Debug[MPI_DebugCount+2],  '0' + v);
	CacheBypassWriteByte(&MPI_Debug[MPI_DebugCount+3], '\n');*/

	// brute force
	//CacheBypassWrite((int*) MPI_Debug, MPI_DebugCount+1);
	CacheBypassWriteInt(&MPI_DebugCount, MPI_DebugCount+4);

}

/**
 * @deprecated use MPI_AddDebugLine
 */
void MPI_AddDebug(char c)
{
	CacheBypassReadInt(&MPI_DebugCount);

//	CacheBypassWriteByte(&MPI_Debug[MPI_DebugCount], c);

	MPI_Debug[MPI_DebugCount] = c;

	// brute force
	CacheBypassWrite((int*) MPI_Debug, MPI_DebugCount);
	CacheBypassWriteInt(&MPI_DebugCount, MPI_DebugCount+1);
}

/**
 *
 */
int MPI_DumpDebug()
{
	int i=0;
	int error = 0;

	CacheBypassReadInt(&MPI_DebugCount);
	printf("debug dump %d bytes\n{\n", MPI_DebugCount);

	CacheBypassRead((int*) MPI_Debug, MPI_DebugCount);

	printf("[%2d]", i);

	for ( i=0; i< MPI_DebugCount; i++)
	{
		char c = MPI_Debug[i];

		if (c == '\n')
			printf("\n");
		else if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			printf("%c", c);
		else
		{
			printf("-");
			error = 1;
		}

		if (c == '\n' && i < (MPI_DebugCount-1))
			printf("[%2X]", (i+1));
	}

	printf("\n}\n");

	return error;
}

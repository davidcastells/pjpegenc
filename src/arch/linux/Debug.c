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
#include "Debug.h"
#include "../../mpi.h"

#include <stdio.h>

char MPI_Debug[0x400*4];
int MPI_DebugCount = 0;

void MPI_DebugInit()
{
    CacheBypassWriteInt(&MPI_DebugCount, 0);
}

void MPI_AddDebugLine(char code, int v)
{
    printf("%d%c%d\n", mpi_rank(), code, v);
}

/**
 * @deprecated use MPI_AddDebugLine
 */
void MPI_AddDebug(char c)
{
    printf("%c", c);
}

/**
 *
 */
int MPI_DumpDebug()
{
    return 0;
}

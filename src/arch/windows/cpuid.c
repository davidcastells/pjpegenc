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
#include "cpuid.h"
#include "../../config.h"

#include <stdio.h>

DWORD mpi_threads[NUM_OF_PROCESSORS];

DWORD ThreadProc (LPVOID lpdwThreadParam ) ;


int getCpuIdentifier()
{
    int i;
    for (i = 0; i < NUM_OF_PROCESSORS; i++)
    {
        if (mpi_threads[i] == GetCurrentThreadId())
            return i;
    }
    
    return -1;
}

void createSlaveThreads(main_func mf)
{
    int i;
    
    mpi_threads[0] = GetCurrentThreadId();
    
    for (i = 1; i < NUM_OF_PROCESSORS; i++)
    {
        DWORD tid;
        
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc, (LPVOID) mf, 0, &tid);

        mpi_threads[i] = tid;

        //printf("Slave %d has handle %p\n", i, mpi_threads[i]);
    }
    
}


DWORD ThreadProc (LPVOID lpdwThreadParam ) 
{
    main_func mf = (main_func) lpdwThreadParam;
    
    //printf("Going to invoke main from thread %p\n", GetCurrentThreadId());
    
    (*mf)(0, NULL);
}
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

#include <pthread.h>

pthread_mutex_t  mutex;


int initMutex()
{
    
    pthread_mutex_init (& mutex , NULL );
    return 0;
}

void mutexAcquire()
{
     pthread_mutex_lock (&mutex );  
}

void mutexRelease()
{
    pthread_mutex_unlock (& mutex );   
}

int mutexState()
{
    return 0;
}
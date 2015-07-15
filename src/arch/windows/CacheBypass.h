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

#ifndef CACHE_BYPASS_H_INCLUDED
#define CACHE_BYPASS_H_INCLUDED

void CacheBypassRead(int* ptr, int size);
int CacheBypassReadInt(int* ptr);
void CacheBypassWriteInt(int* ptr, int v);
void CacheBypassWriteByte(char* ptr, char v);
void CacheBypassReadMemcpy(int* dst, int* src, int size);
void CacheBypassWriteMemcpy(int* dst, int* src, int size);
void CacheBypassBothMemcpy(int* dst, int* src, int size);


#endif
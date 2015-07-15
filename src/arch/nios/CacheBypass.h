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
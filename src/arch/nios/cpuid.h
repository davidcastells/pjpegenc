#ifndef CPUUID_H_
#define CPUUID_H_

#define RETURN_CPU_IDENTIFIER() register int cpuid;NIOS2_READ_CPUID(cpuid);return cpuid;


#endif

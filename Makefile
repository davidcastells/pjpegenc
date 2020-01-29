all: baseline seqmem threads
clean:	baseline_clean seqmem_clean threads_clean
	
baseline:
	$(MAKE) -C src/baseline

seqmem:
	$(MAKE) -C src/seqmem
	
threads:
	$(MAKE) -C src/phases
	
baseline_clean:
	$(MAKE) -C src/baseline clean

seqmem_clean:
	$(MAKE) -C src/seqmem clean
	
threads_clean:
	$(MAKE) -C src/phases clean

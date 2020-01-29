all: baseline seqmem threads
	
baseline:
	$(MAKE) -C src/baseline

seqmem:
	$(MAKE) -C src/seqmem
	
threads:
	$(MAKE) -C src/phases
	

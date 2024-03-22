all: baseline seqmem phases 
clean:	baseline_clean seqmem_clean phases_clean 
	
baseline:
	$(MAKE) -C src/baseline

seqmem:
	$(MAKE) -C src/seqmem
	
phases:
	$(MAKE) -C src/phases

opencl_fpga_s1:
	$(MAKE) -C src/opencl_fpga_s1

opencl_gpu_s1:
	$(MAKE) -C src/opencl_fpga_s1
	
baseline_clean:
	$(MAKE) -C src/baseline clean

seqmem_clean:
	$(MAKE) -C src/seqmem clean
	
phases_clean:
	$(MAKE) -C src/phases clean

opencl_fpga_s1_clean:
	$(MAKE) -C src/opencl_fpga_s1 clean

ompss_fpga:
	$(MAKE) -C src/ompss_fpga

ompss_fpga_clean:
	$(MAKE) -C src/ompss_fpga clean

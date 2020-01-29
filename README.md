# pjpegenc
pjpegenc is a project to do research in strategies to parallelize "classic" jpeg encoding

The code is organized in several directories that present a different implementation of the algorithm.
In each directory there is a Makefile.

Current Directories:

## baseline 
Baseline version that is used as golden model to compare alternative versions. 
In this version color space conversion (from RGB to YCbCr) is done from the 
whole image prior to start the DCT/Q/Huf pipeline at block level. 
This increases the demand for memory.

## seqmem 
In this version the color space conversion is done in a block basis, so that 
the processing pipeline does Color/DCT/Q/Huf. This minimizes the memory needed. 

## phases
In this version we try do work in phases with the whole image rather than the 
original block oriented processing followed by the baseline

## opencl_fpga_s1
In this version we will try to accelerate some part of the algorithm with 
an OpenCL kernel 

## Citation 
I would appreciate that you cite us

@inproceedings{castells2010scalability,
  title={Scalability of a Parallel JPEG Encoder on Shared Memory Architectures},
  author={Castells-Rufas, David and Joven, Jaume and Carrabina, Jordi},
  booktitle={2010 39th International Conference on Parallel Processing},
  pages={502--507},
  year={2010},
  organization={IEEE}
}

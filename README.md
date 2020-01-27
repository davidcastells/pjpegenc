# pjpegenc
pjpegenc is a project to do research in strategies to parallelize "classic" jpeg encoding

The code is organized in several directories that present a different implementation of the algorithm.
In each directory there is a Makefile.

Current Directories:

baseline = Baseline version that is used as golden model to compare alternative versions. In this version color space conversion (from RGB to YCbCr) is done from the whole image prior to start the DCT/Q/Huf pipeline at block level. This increases the demand for memory.

seqmem = In this version the color space conversion is done in a block basis, so that the processing pipeline does Color/DCT/Q/Huf. This minimizes the memory needed. 

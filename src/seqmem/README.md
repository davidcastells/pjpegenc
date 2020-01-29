When working with embedded platforms with memory limitations we have to minimize 
the use of memory.

In the baseline the RGB image information is stored and then it is converted to 
YCrCb as a whole block. Both color spaces (RGB and YCrCb) are mantained in 
memory at the same time, but just one is used.

Since the YCrCb info is accessed in block order (just once) it can be computed 
when accessed block by block, instead of the precomputation that is done in 
JPegInfo. This reduces the amount of memory required to do the compression.

The DCT, Quantization and Hufman encoding are done in sequential order per 
every block.

To simplify the processing and memory handling, we removed the color downsampling
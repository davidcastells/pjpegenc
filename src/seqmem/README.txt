When working with embedded platforms with memory limitations we have to minimize the use of memory.

In the baseline the RGB image information is stored and then it is converted to YCrCb.

Both color spaces are mantained in memory at the same time, but just one is used.
Since the YCrCb info is accessed in block order (just once) it can be computed when accessed block by block, 
instead of the precomputation that is done in JPegInfo
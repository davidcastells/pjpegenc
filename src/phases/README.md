Data parallel approaches typically require that we are able to work with a large
amount of data.

In this version we do each space transformation for the biggest possible amount 
of data at a time. For instance, all DCT blocks are computed before doing Quantization. 

This increases the amount of required data, but increases the possibility of taking 
profit of data parallelism.
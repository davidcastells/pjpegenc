CC = g++
CC_FLAGS=-DLINUX -O2 -g
LINK=$(CC) -o $@  $< 

EXEC = pjpegenc_ompss_fpga
SOURCES = main.cpp ../Bitmap.cpp ../FileOutputStream.cpp JpegEncoder.cpp DCT.cpp ../Huffman.cpp \
    JpegInfo.cpp ../OutputStream.cpp ../BufferedOutputStream.cpp ../EmbeddedImage.cpp \
    ../ByteArrayOutputStream.cpp ../arch/linux/PerformanceCounter.cpp

OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@


all: $(EXEC)
	
clean:
	rm -f $(EXEC) $(OBJECTS)
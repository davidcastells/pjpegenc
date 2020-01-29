CC = g++
CC_FLAGS=-DLINUX -O2 -g
LINK=$(CC) -o $@  $< 

EXEC = pjpegenc_phases
SOURCES = main.cpp ../Bitmap.cpp ../FileOutputStream.cpp JpegEncoder.cpp ../DCT.cpp ../Huffman.cpp \
    JpegInfo.cpp ../OutputStream.cpp ../BufferedOutputStream.cpp ../EmbeddedImage.cpp \
    ../ByteArrayOutputStream.cpp ../arch/linux/PerformanceCounter.cpp

OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)
	
$(EXEC)_profile: $(OBJECTS)
	$(CC) -pg $(OBJECTS) -o $(EXEC)_gprof

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@


all: $(EXEC)
	
profile: $(EXEC)_profile
	
clean:
	rm -f $(EXEC) $(OBJECTS)
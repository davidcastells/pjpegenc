CC = g++
CC_FLAGS=-DWIN32 -O3
LINK=$(CC) -o $@  $< 

EXEC = pjpegenc
SOURCES = main.cpp ../FileOutputStream.cpp JpegEncoder.cpp ../DCT.cpp ../Huffman.cpp \
    JpegInfo.cpp ../OutputStream.cpp ../BufferedOutputStream.cpp ../EmbeddedImage.cpp \
    ../ByteArrayOutputStream.cpp ../arch/windows/PerformanceCounter.cpp

OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@


all: $(EXEC)
	
clean:
	rm -f $(EXEC) $(OBJECTS)

SOURCES_DIR = ../../src
BUILD_DIR = .

CC = g++
CC_FLAGS=-DLINUX -O0 -g -I $(SOURCES_DIR)/arch/linux
LINK=$(CC) -o $@  $< 

EXEC = pjpegenc_baseline

SOURCES = $(SOURCES_DIR)/baseline/main.cpp $(SOURCES_DIR)/FileOutputStream.cpp $(SOURCES_DIR)/Bitmap.cpp \
	$(SOURCES_DIR)/baseline/JpegEncoder.cpp $(SOURCES_DIR)/DCT.cpp $(SOURCES_DIR)/Huffman.cpp \
	$(SOURCES_DIR)/baseline/JpegInfo.cpp $(SOURCES_DIR)/OutputStream.cpp $(SOURCES_DIR)/BufferedOutputStream.cpp $(SOURCES_DIR)/EmbeddedImage.cpp \
	$(SOURCES_DIR)/ByteArrayOutputStream.cpp $(SOURCES_DIR)/arch/linux/PerformanceCounter.c


$(EXEC): $(SOURCES)
	$(CC) $(CC_FLAGS) $(SOURCES) -o $(EXEC)


all: $(EXEC)
	
clean:
	rm -f $(EXEC) 

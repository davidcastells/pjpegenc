// 17/12/2013
// This encoder implemented by David Castells-Rufas (david.castells@uab.cat)
// to do research in parallel implementation of the JPEG encoding algorithm
// The code is implemented in C++ and derived from a Java version
//
// The application contains code from (at least) the following authors
//      James R. Weeks (James@obrador.com)
//      Florian Raemy
//      Benjamin Kalytta
//      Vladimir Antonenko
//      Thomas G. Lane
//
#include "JpegEncoder.h"
#include "Bitmap.h"
#include "FileOutputStream.h"

#include <stdio.h>

/**
 *  The application assumes that there is a test.bmp image in the current directory
 *  and creates a resulting test.jpg with the encoded file
 */
int main(int argc, char* args[])
{	
	printf("Jpeg Encoder Test " __TIMESTAMP__ "\n");
	
	CBitmap bitmap;
	
	if (bitmap.load("test.bmp"))
		printf("Loaded test.bmp\n");
	else
	{
		printf("Failed to load test.bmp\n");
		exit(1);
	}
	
	FileOutputStream fos("test.jpg");
	JpegEncoder encoder(&bitmap, 80, &fos);
        encoder.Compress();
	return 0;
	
}
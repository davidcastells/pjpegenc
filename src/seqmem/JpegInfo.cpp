// 17/12/2013
// This encoder implemented by David Castells-Rufas (david.castells@uab.cat)
// to do research in parallel implementation of the JPEG encoding algorithm
// The code is implemented in C++ and derived from a Java version, see previous
// author licences below
//
#include "JpegInfo.h"

#include "../Image.h"
#include "../Matrix.h"
#include "../globals.h"


#include <math.h>
#include <stdio.h>
#include <assert.h>

/*
 * JpegInfo - Given an image, sets default information about it and divides
 * it into its constituant components, downsizing those that need to be.
 */


	JpegInfo::~JpegInfo()
	{
	}
	
    JpegInfo::JpegInfo(Image* image)
    {
    	imageobj = image;
        imageWidth = image->getWidth();
        imageHeight = image->getHeight();
        Comment = "pjpegenc, David Castells-Rufas";

        if (verbose)
        {
            printf("Image Size: %d x %d \n", imageWidth, imageHeight);
        }
        CompID[0] = 1;
         CompID[1] = 2;
         CompID[2] = 3;

         HsampFactor[0] = 1;
         HsampFactor[1] = 1;
         HsampFactor[2] = 1;

         VsampFactor[0] = 1;
         VsampFactor[1] = 1;
         VsampFactor[2] = 1;

         QtableNumber[0] = 0;
         QtableNumber[1] = 1;
         QtableNumber[2] = 1;

         DCtableNumber[0] = 0;
         DCtableNumber[1] = 1;
         DCtableNumber[2] = 1;

    	 ACtableNumber[0] = 0;
    	 ACtableNumber[1] = 1;
    	 ACtableNumber[2] = 1;

    	 lastColumnIsDummy[0] = false;
    	 lastColumnIsDummy[1] = false;
    	 lastColumnIsDummy[2] = false;

    	 lastRowIsDummy[0] = false;
    	 lastRowIsDummy[1] = false;
    	 lastRowIsDummy[2] = false;

    	 Ss = 0;
    	 Se = 63;
    	 Ah = 0;
    	 Al = 0;

         Precision = 8;

         if (verbose)
            printf("Create Arrays\n");
         
         getYCCArray();
        
         
    
         
    }

    void JpegInfo::setComment(std::string comment) 
    {
        Comment = Comment + comment;
    }

    std::string JpegInfo::getComment() 
    {
        return Comment;
    }

    /*
     * This method creates and fills three arrays, Y, Cb, Cr using the
     * input image.
     */

    void JpegInfo::getYCCArray()
    {
        int r, g, b, y, x;

        
        MaxHsampFactor = 1;
        MaxVsampFactor = 1;

        for (y = 0; y < NUMBER_OF_COMPONENTS; y++)
        {
            MaxHsampFactor = std::max(MaxHsampFactor, HsampFactor[y]);
            MaxVsampFactor = std::max(MaxVsampFactor, VsampFactor[y]);
        }
        
        assert(MaxHsampFactor == 1);
        assert(MaxVsampFactor == 1);
        
        if (verbose)
        {
            printf("Sampling factor %d x %d\n", MaxHsampFactor, MaxVsampFactor);
        }
        
        for (y = 0; y < NUMBER_OF_COMPONENTS; y++)
        {
                compWidth[y] = (((imageWidth%8 != 0) ? ((int) ceil((double) imageWidth/8.0))*8 : imageWidth)/MaxHsampFactor)*HsampFactor[y];
                if (compWidth[y] != ((imageWidth/MaxHsampFactor)*HsampFactor[y])) 
                {
                        lastColumnIsDummy[y] = true;
                }
                // results in a multiple of 8 for compWidth
                // this will make the rest of the program fail for the unlikely
                // event that someone tries to compress an 16 x 16 pixel image
                // which would of course be worse than pointless
                BlockWidth[y] = (int) ceil((double) compWidth[y]/8.0);
                compHeight[y] = (((imageHeight%8 != 0) ? ((int) ceil((double) imageHeight/8.0))*8: imageHeight)/MaxVsampFactor)*VsampFactor[y];
                if (compHeight[y] != ((imageHeight/MaxVsampFactor)*VsampFactor[y])) {
                        lastRowIsDummy[y] = true;
                }
                BlockHeight[y] = (int) ceil((double) compHeight[y]/8.0);
        }
        
    }
    
    void JpegInfo::getYCrCb(int comp, int y, int x, float dctArray1[8][8])
    {
        int r,g,b;
        float v;

        for (int a = 0; a < 8; a++)
        {
            for (int xb = 0; xb < 8; xb++)
            {
                imageobj->getRGB(x+xb, y+a, &r, &g, &b);

                switch (comp)
                {
                    case 0: // Y
                        v = (float)((0.299 * (float)r + 0.587 * (float)g + 0.114 * (float)b));
                        break;
                    case 1: // Cr
                        v = 128 + (float)((-0.16874 * (float)r - 0.33126 * (float)g + 0.5 * (float)b));
                        break;
                    case 2: // Cb
                        v =  128 + (float)((0.5 * (float)r - 0.41869 * (float)g - 0.08131 * (float)b));
                        break;
                }

                dctArray1[a][xb] = v;                              
            }
        }
    }


    /*
    float[][] DownSample(float[][] C, int comp)
    {
        int inrow, incol;
        int outrow, outcol;
        float output[][];
        int temp;
        int bias;
        inrow = 0;
        incol = 0;
        output = new float[compHeight[comp]][compWidth[comp]];
        for (outrow = 0; outrow < compHeight[comp]; outrow++) {
                bias = 1;
                for (outcol = 0; outcol < compWidth[comp]; outcol++) {
                        output[outrow][outcol] = (C[inrow][incol++] + C[inrow++][incol--] + C[inrow][incol++] + C[inrow--][incol++] + (float)bias)/(float)4.0;
                        bias ^= 3;
                }
                inrow += 2;
                incol = 0;
        }
        return output;
    }*/

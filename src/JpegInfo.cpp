// 17/12/2013
// This encoder implemented by David Castells-Rufas (david.castells@uab.cat)
// to do research in parallel implementation of the JPEG encoding algorithm
// The code is implemented in C++ and derived from a Java version, see previous
// author licences below
//
#include "JpegInfo.h"

#include "image.h"
#include "Matrix.h"

#include <math.h>

/*
 * JpegInfo - Given an image, sets default information about it and divides
 * it into its constituant components, downsizing those that need to be.
 */


	JpegInfo::~JpegInfo()
	{
		delete [] Components[0];
		delete [] Components[1];
		delete [] Components[2];
	}
	
    JpegInfo::JpegInfo(Image* image)
    {
    	imageobj = image;
        imageWidth = image->getWidth();
        imageHeight = image->getHeight();
        Comment = "JPEG Encoder Copyright 1998, James R. Weeks anｄ BioElectroMech.  ";

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
     * This method creates anｄ fills three arrays, Y, Cb, anｄ Cr using the
     * input image.
     */

    void JpegInfo::getYCCArray()
    {
        int* values[imageWidth * imageHeight];
        int r, g, b, y, x;

        
        MaxHsampFactor = 1;
        MaxVsampFactor = 1;

        for (y = 0; y < NUMBER_OF_COMPONENTS; y++)
        {
                MaxHsampFactor = std::max(MaxHsampFactor, HsampFactor[y]);
                MaxVsampFactor = std::max(MaxVsampFactor, VsampFactor[y]);
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
        
        
    	
        Matrix<float>* Y = new Matrix<float>(compHeight[0], compWidth[0]);
        Matrix<float>* Cr1 = new Matrix<float>(compHeight[0], compWidth[0]);
        Matrix<float>* Cb1 = new Matrix<float>(compHeight[0], compWidth[0]);
        //Matrix<float>* Cb2 = new Matrix<float>(compHeight[1], compWidth[1]);
        //Matrix<float>* Cr2 = new Matrix<float>(compHeight[2], compWidth[2]);
        
        Components[0] = Y;
//        Cb2 = DownSample(Cb1, 1);
        Components[1] = Cb1;
//        Cr2 = DownSample(Cr1, 2);
        Components[2] = Cr1;

        int index = 0;
        for (y = 0; y < imageHeight; ++y)
    	{
            for (x = 0; x < imageWidth; ++x)
    	    {
                /*int value = imageobj->getRGB();
                r = ((value >> 16) & 0xff);
                g = ((value >> 8) & 0xff);
                b = (value  & 0xff);*/
                imageobj->getRGB(x, y, &r, &g, &b);

// The following three lines are a more correct color conversion but
// the current conversion technique is sufficient anｄ results in a higher
// compression rate.
//                Y[y][x] = 16 + (float)(0.8588*(0.299 * (float)r + 0.587 * (float)g + 0.114 * (float)b ));
//                Cb1[y][x] = 128 + (float)(0.8784*(-0.16874 * (float)r - 0.33126 * (float)g + 0.5 * (float)b));
//                Cr1[y][x] = 128 + (float)(0.8784*(0.5 * (float)r - 0.41869 * (float)g - 0.08131 * (float)b));
                Y->put(y, x, (float)((0.299 * (float)r + 0.587 * (float)g + 0.114 * (float)b)));
                Cb1->put(y, x,  128 + (float)((-0.16874 * (float)r - 0.33126 * (float)g + 0.5 * (float)b)));
                Cr1->put(y, x,  128 + (float)((0.5 * (float)r - 0.41869 * (float)g - 0.08131 * (float)b)));
                
    	    }
    	}

// Need a way to set the H and V sample factors before allowing downsampling.
// For now (04/04/98) downsampling must be hard coded.
// Until a better downsampler is implemented, this will not be done.
// Downsampling is currently supported.  The downsampling method here
// is a simple box filter.

        
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

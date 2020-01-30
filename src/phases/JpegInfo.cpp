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

/*
 * JpegInfo - Given an image, sets default information about it and divides
 * it into its constituant components, downsizing those that need to be.
 */


    JpegInfo::~JpegInfo()
    {
        freeImage();
    }
	
    void JpegInfo::freeImage()
    {
        if (imageobj != NULL)
        {
            delete imageobj;
            imageobj = NULL;
        }
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

//         if (verbose)
//            printf("Create Arrays\n");
//         
//         getYCCArray();
        
         MaxHsampFactor = 1;
        MaxVsampFactor = 1;

        for (int y = 0; y < NUMBER_OF_COMPONENTS; y++)
        {
            MaxHsampFactor = std::max(MaxHsampFactor, HsampFactor[y]);
            MaxVsampFactor = std::max(MaxVsampFactor, VsampFactor[y]);
        }
        
        if (verbose)
        {
            printf("Sampling factor %d x %d\n", MaxHsampFactor, MaxVsampFactor);
        }
        
        for (int y = 0; y < NUMBER_OF_COMPONENTS; y++)
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
                
                if (compHeight[y] != ((imageHeight/MaxVsampFactor)*VsampFactor[y])) 
                {
                        lastRowIsDummy[y] = true;
                }
                BlockHeight[y] = (int) ceil((double) compHeight[y]/8.0);
        }
    
         
    }

    void JpegInfo::setComment(std::string comment) 
    {
        Comment = Comment + comment;
    }

    std::string JpegInfo::getComment() 
    {
        return Comment;
    }

    /**
     * This method creates and fills three arrays, Y, Cb, Cr using the
     * input image.
     */
    void JpegInfo::rgbToYCrCb(Matrix5D<float>* dctArray1)
    {
        int comp, r,c, b, y, x;
        int rc, gc, bc;

        
        
        
        // assume they are all the same (no subsampling)
        int MinBlockHeight = BlockHeight[0];    
        int MinBlockWidth = BlockWidth[0];

        for (comp = 0; comp < NUMBER_OF_COMPONENTS; comp++)
        {
           for (r = 0; r < MinBlockHeight; r++)
            {
               for (c = 0; c < MinBlockWidth; c++)
               {
                    for (y = 0; y < 8; y++)
                    {
                       for (x = 0; x < 8; x++)
                       {
                           imageobj->getRGB(x, y, &rc, &gc, &bc);

                            // The following three lines are a more correct color conversion but
                            // the current conversion technique is sufficient and results in a higher
                            // compression rate.
                            //                Y[y][x] = 16 + (float)(0.8588*(0.299 * (float)r + 0.587 * (float)g + 0.114 * (float)b ));
                            //                Cb1[y][x] = 128 + (float)(0.8784*(-0.16874 * (float)r - 0.33126 * (float)g + 0.5 * (float)b));
                            //                Cr1[y][x] = 128 + (float)(0.8784*(0.5 * (float)r - 0.41869 * (float)g - 0.08131 * (float)b));
                            dctArray1->put(0, r, c, y, x, (float)((0.299 * (float)rc + 0.587 * (float)gc + 0.114 * (float)bc)));
                            dctArray1->put(1, r, c, y, x,  128 + (float)((-0.16874 * (float)rc - 0.33126 * (float)gc + 0.5 * (float)bc)));
                            dctArray1->put(2, r, c, y, x,  128 + (float)((0.5 * (float)rc - 0.41869 * (float)gc - 0.08131 * (float)bc)));
                       }
                    }
               }
           }
        }
    }

    

// 17/12/2013
// This encoder implemented by David Castells-Rufas (david.castells@uab.cat)
// to do research in parallel implementation of the JPEG encoding algorithm
// The code is implemented in C++ and derived from a Java version, see previous
// author licences below
//

#ifndef DCT_H_INCLUDED_
#define DCT_H_INCLUDED_

#include "../globals.h"

// This class incorporates quality scaling as implemented in the JPEG-6a
// library.
#define N 8

 /*
 * DCT - A Java implementation of the Discreet Cosine Transform
 */

    /**
     * DCT Block Size - default 8
     */

    /**
     * Image Quality (0-100) - default 80 (good image / good compression)
     */
extern     int DCT_QUALITY;

extern int DCT_quantum[2][N*N];
extern BIGFP DCT_Divisors[2][N*N];
     
/**
 * Quantitization Matrix for luminace.
 */
extern int* DCT_quantum_luminance;
extern BIGFP* DCT_DivisorsLuminance;

/**
 * Quantitization Matrix for chrominance.
 */
extern int* DCT_quantum_chrominance;
extern BIGFP* DCT_DivisorsChrominance;

    /**
     * Constructs a new DCT object. Initializes the cosine transform matrix
     * these are used when computing the DCT anｄ it's inverse. This also
     * initializes the run length counters anｄ the ZigZag sequence. Note that
     * the image quality can be worse than 25 however the image will be
     * extemely pixelated, usually to a block size of N.
     *
     * @param QUALITY The quality of the image (0 worst - 100 best)
     *
     */
    void DCT_DCT();

    void DCT_init(int QUALITY);


    /*
     * This method sets up the quantization matrix for luminance and
     * chrominance using the Quality parameter.
     */
    void DCT_initMatrix(int quality);

    /*
     * This method preforms forward DCT on a block of image data using
     * the literal method specified for a 2-D Discrete Cosine Transform.
     * It is included as a curiosity anｄ can give you an idea of the
     * difference in the compression result (the resulting image quality)
     * by comparing its output to the output of the AAN method below.
     * It is ridiculously inefficient.
     */

// For now the final output is unusable.  The associated quantization step
// needs some tweaking.  If you get this part working, please let me know.


    void DCT_forwardDCTExtreme(float input[N][N], BIGFP output[N][N]);


    /*
     * This method preforms a DCT on a block of image data using the AAN
     * method as implemented in the IJG Jpeg-6a library.
     */
     void DCT_forwardDCT(float input[N][N], BIGFP output[N][N]);
    void DCT_forwardDCT(float* input, BIGFP output[8][8]);
    void DCT_forwardDCT(float* input, BIGFP* output);

    /*
    * This method quantitizes data and rounds it to the nearest integer.
    */
    void DCT_quantizeBlock(BIGFP inputData[N][N], int code, int outputData[N*N] );
    void DCT_quantizeBlock(BIGFP* inputData, int code, int* outputData);
    
    /*
    * This is the method for quantizing a block DCT'ed with forwardDCTExtreme
    * This method quantitizes data anｄ rounds it to the nearest integer.
    */
     void DCT_quantizeBlockExtreme(BIGFP inputData[N][N], int code, int outputData[N*N]);


#endif
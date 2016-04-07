#include "testing.h"

/*
 * SpeakerDistance
 * Takes 5 parameters:
 * 1. input - The sound file as an array of shorts (some may be negative values)
 * 2. words - the struct of word indices
 * 3. word - which word we're analyzing
 * 4. order - the order used for determining the coefficients
 * 5. lpc - the lpc coefficient (for a user) we're checking against
 *
 * Returns the distance found when checking the word's coefficient against the given lpc coefficient
 */
float SpeakerDistance(short* input, struct word* words, int word, int order, struct LPC_data* lpc)
{
    clock_t time = clock();             // initialize timestamp
    
    // Calculate a
    struct matrix a; // there are 15 words spoken. a[x] accesses the "a" coefficient for the x'th word we're looking at.
    struct matrix littleR = CreateMatrix(order, 1);
    struct matrix bigR = CreateMatrix(order, order);
        
    for (unsigned int j = words[word].start + order + 1; j < words[word].end; j++) // j loops through the individual data of each word
    {
        struct matrix sn = CreateMatrix(order, 1);
        for (unsigned int k = 0; k < order; k++)
            sn.element[k][0] = input[j-k-1];
        littleR = AddMatrix(littleR, ScaleMatrix(sn, input[j]));
        bigR = AddMatrix(bigR, MultiplyMatrix(sn, TransposeMatrix(sn)));
    }
    a = MultiplyMatrix(InverseMatrix(bigR), littleR);
    
    DeleteMatrix(littleR);
    DeleteMatrix(bigR);
    
    float distance = MultiplyMatrix(MultiplyMatrix(TransposeMatrix(SubMatrix(a, lpc->mu)), InverseMatrix(lpc->covariance)), SubMatrix(a, lpc->mu)).element[0][0];
    DeleteMatrix(a);
    
    //printf("SpeakerDistance() ran. Time: %fms\n",((double)(clock()-time)*1000/CLOCKS_PER_SEC));
    return distance;
}
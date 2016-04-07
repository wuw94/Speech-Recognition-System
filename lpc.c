#include "lpc.h"

/*
 * LPC
 * Takes 3 parameters:
 * 1. input - The sound file as an array of shorts (some may be negative values)
 * 2. words - the struct of word indices
 * 3. order - order used for determining the coefficients
 *
 * Returns a struct of the mu and covariance found (two matrices)
 */
struct LPC_data* LPC(short* input, struct word* words, int order)
{
    clock_t time = clock();             // initialize timestamp
    
    // Calculate a
    struct matrix a[15]; // there are 15 words spoken. a[x] accesses the "a" coefficient for the x'th word we're looking at.
    for (unsigned int i = 0; i < 15; i++) // i loops through the words we're indexing (15)
    {
        struct matrix littleR = CreateMatrix(order, 1);
        struct matrix bigR = CreateMatrix(order, order);

        for (unsigned int j = words[i].start + order + 1; j < words[i].end; j++) // j loops through the individual data of each word
        {
            struct matrix sn = CreateMatrix(order, 1);
            for (unsigned int k = 0; k < order; k++)
                sn.element[k][0] = input[j-k-1];
            littleR = AddMatrix(littleR, ScaleMatrix(sn, input[j]));
            bigR = AddMatrix(bigR, MultiplyMatrix(sn, TransposeMatrix(sn)));
            DeleteMatrix(sn);
        }
        a[i] = MultiplyMatrix(InverseMatrix(bigR), littleR);
        
        DeleteMatrix(littleR);
        DeleteMatrix(bigR);
    }
    
    // Calculate mu
    struct matrix mu = CreateMatrix(order, 1);
    for (unsigned int i = 0; i < order; i++)
        for (unsigned int j = 0; j < 15; j++)
            mu.element[i][0] += a[j].element[i][0] / 15;
    
    // Calculate covariance
    struct matrix covariance = CreateMatrix(order, order);
    for (unsigned int i = 0; i < order; i++)
        for (unsigned int j = 0; j < order; j++)
            for (unsigned int k = 0; k < 15; k++)
                covariance.element[i][j] += MultiplyMatrix( SubMatrix(a[k], mu), TransposeMatrix(SubMatrix(a[k], mu)) ).element[i][j] / 15;
                
    for (unsigned int i = 0; i < 15; i++)
        DeleteMatrix(a[i]);
                
    static struct LPC_data result;
    result.mu = mu;
    result.covariance = covariance;
    

    //printf("LPC() ran. Time: %fms\n",((double)(clock()-time)*1000/CLOCKS_PER_SEC));
    return &result;
}
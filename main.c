#include <stdio.h>

#include "user_inputs.h"
#include "word_isolation.h"
#include "matrix.h"
#include "lpc.h"
#include "testing.h"

void main()
{
    while(1)
    {
        unsigned int order = 15;
        
        struct word* words1 = GetWords(user1,66,4); //input,windowsize,threshold
        struct word* words2 = GetWords(user2,66,4);
        
        struct LPC_data* lpc1 = LPC(user1, words1, order);
        struct LPC_data* lpc2 = LPC(user2, words2, order);
        
        
        // Start Testing
        
        int test_start = 15;
        int test_end = 30;
        int total = 0;
        int correct = 0;
        
        for (unsigned int i = test_start; i < test_end; i++)
        {
            printf("Word %d spoken by User1, matched against:\n",i);
            float u1 = SpeakerDistance(user1, words1, i, order, lpc1);
            printf("  User1: %f\n", u1);
            float u2 = SpeakerDistance(user1, words1, i, order, lpc2);
            printf("  User2: %f\n", u2);
            total++;
            if (u1 <= u2)
                correct++;
        }
        
        for (unsigned int i = test_start; i < test_end; i++)
        {
            printf("Word %d spoken by User2, matched against:\n",i);
            float u1 = SpeakerDistance(user2, words2, i, order, lpc1);
            printf("  User1: %f\n", u1);
            float u2 = SpeakerDistance(user2, words2, i, order, lpc2);
            printf("  User2: %f\n", u2);
            total++;
            if (u1 >= u2)
                correct++;
        }
        
        printf("---------- Result ----------\n");
        printf("Correct tests: %d\n",correct);
        printf("Total tests: %d\n",total);
        printf("Percent Passed: %f\n",(float)correct/total);
        
        break;
    }
    
}



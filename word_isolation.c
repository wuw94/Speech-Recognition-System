#include "word_isolation.h"

/* 
 * GetWords
 * Takes 3 parameters:
 * 1. input - The sound file as an array of shorts (some may be negative values)
 * 2. window_size - size of windowing function for computing moving average
 * 3. threshold - threshold for detecting a valid word
 * 
 * Returns the words found (a struct of their indices) found by the function
 */
struct word* GetWords(short* data, unsigned int window_size, short threshold)
{
    clock_t time = clock();             // initialize timestamp
    
    static struct word result[1000];      // result to return
    unsigned int words_found = 0;       // keep track of how many words we found
    unsigned int word_start = 0;   // check to determine beginning or end of word
    
    for (unsigned int index = 0; index < 320000; index++)
    {
        short moving_average = 0;
        for (unsigned int i = index - window_size; i < index; i++)
            moving_average += (index - window_size < 0) ? 0 : abs(data[i]);
        moving_average /= (index > 0 && index < window_size) ? index : window_size;

        if (!word_start && moving_average > threshold)
            word_start = index;
        else if (word_start && moving_average < threshold)
        {
            if (index - word_start > 4000 && index - word_start < 9000)
            {
                result[words_found].start = word_start;
                result[words_found].end = index;
                words_found++;
                if (words_found > 31)
                    printf("Warning: Words detected exceeds 31\n");
                //printf("Word %d, length %d, starting at %d\n",words_found,index-word_start,word_start);
            }
            word_start = 0;
        }
    }
    
    printf("GetWords() ran, found %d words. Time: %fms\n", words_found,((double)(clock()-time)*1000/CLOCKS_PER_SEC));
    return result;
}

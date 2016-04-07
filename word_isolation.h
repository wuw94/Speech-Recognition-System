#ifndef word_isolation_h
#define word_isolation_h

#include <stdio.h>
#include <time.h>

struct word
{
    int start;
    int end;
};

struct word* GetWords(short* input, unsigned int window_size, short threshold);

#endif
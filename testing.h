#ifndef testing_h
#define testing_h

#include <stdio.h>
#include "lpc.h"

float SpeakerDistance(short* data, struct word* words, int word, int order, struct LPC_data* lpc);
#endif

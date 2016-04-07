//
//  lpc.h
//  CSE135B Lab4
//
//  Created by Wesley Wu on 3/10/16.
//  Copyright © 2016 Wesley Wu. All rights reserved.
//

#ifndef lpc_h
#define lpc_h

#include <stdio.h>
#include <time.h>
#include "word_isolation.h"
#include "matrix.h"

struct LPC_data
{
    struct matrix mu;
    struct matrix covariance;
};


struct LPC_data* LPC(short* data, struct word* words, int order);

#endif
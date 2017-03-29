#ifndef GOL_C_DELAY_H
#define GOL_C_DELAY_H

#include<time.h>

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

#endif
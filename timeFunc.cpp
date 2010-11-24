#include "timeFunc.h"
//implementation for various time related functions

void delay(int wait) //makes delays in seconds
{
    timeval currTime;
    gettimeofday(&currTime,NULL);
    timeval start = currTime;
    do{
        gettimeofday(&currTime,NULL);
        //cout << start.tv_sec << "\t" << currTime.tv_sec << endl;
    }while((currTime.tv_sec-start.tv_sec) < wait);
}

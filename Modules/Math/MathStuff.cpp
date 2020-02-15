#include "MathStuff.h"
#include <stdlib.h>
#include <time.h>

// TODO: srand (time(NULL));
int RandomNumber()
{
    return rand();
}

float RandomNumberInRange(float min, float max)
{
    return ((rand()) / (RAND_MAX / (max - min)) + min);
};
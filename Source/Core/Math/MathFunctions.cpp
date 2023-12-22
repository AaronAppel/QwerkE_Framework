#include "MathFunctions.h"

#include <stdlib.h>

int RandomNumber()
{
	// #TODO Confirm if srand has been called/seeded
	return rand();
}

int RandomInt(int max, int min)
{
	return (rand() % (max - min + 1)) + min;
}

int RandInRange(int min, int max)
{
	return rand() / (RAND_MAX / (max - min)) + min;
}

float RandInRange(float min, float max)
{
	return rand() / (RAND_MAX / (max - min)) + min;
}

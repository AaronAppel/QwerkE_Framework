#include <stdlib.h>

int RandomInt(int max, int min) // Returns random integer within range
{
	return (rand() % (max - min + 1)) + min;
}

float RandFloatInRange(float min, float max)
{
	return rand() / (RAND_MAX / (max - min)) + min;
}
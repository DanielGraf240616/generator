#ifndef FindClosest_H
#define FindClosest_H

#include <stddef.h>

extern float amplitudeArray[256];

float findClosestIndex(float* array, size_t size, float target);
void createAmplitudeArray(float* amplitudeArray);
#endif

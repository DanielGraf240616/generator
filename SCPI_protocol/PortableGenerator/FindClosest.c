#include <stddef.h>
#include <stdio.h>
#include <math.h>



#define AMPLITUDESTEP 0.12

//Create an array of all possible amplitudes
void createAmplitudeArray(float* amplitudeArray)
{
    for (int i = 0; i < 101; i++)
    {
        amplitudeArray[i] = i * AMPLITUDESTEP;
        //printf("% .2f\n", amplitudeArray[i]);
    }
}



typedef struct { //Structure cointaining position of the value & the closest value 
    size_t position;
    float value;
} ClosestResult;

ClosestResult findClosest(float* array, size_t size, float target) {
    ClosestResult result;
    result.position = 0;
    result.value = array[0];
    float minDelta = fabsf(target - result.value);

    for (size_t i = 1; i < size; i++) {
        float delta = fabsf(target - array[i]);
        if (delta < minDelta) {
            result.position = i;
            result.value = array[i];
            minDelta = delta;
        }
    }
    return result;
}
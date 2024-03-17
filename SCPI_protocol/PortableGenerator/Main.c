#include <stdio.h>
#include "SCPI.h"
#include "FindClosest.h"

char command[20];
float batteryVoltage = 3.6;
float amplitudeArray[256];
float amplitudeCommand = 11.8;


int main()
{
    createAmplitudeArray(amplitudeArray); //Populate array with all possible amplitude values
    //char command[] = "ampl:0"; //User input
    InputCommand(); //Command input
    SCPI(command); //Command process
    createAmplitudeArray(amplitudeArray);
    //findClosestIndex(amplitudeArray, sizeof(amplitudeArray), amplitudeCommand);
}



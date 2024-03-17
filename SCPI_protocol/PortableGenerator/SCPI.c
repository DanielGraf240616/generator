#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "FindClosest.h"

extern float batteryVoltage;
extern float amplitudeArray[];

char command[20];
char command_type[20];
char command_value_str[20];
int output_mode = 0;
char waveform[20];
float amplitude = 0.0;
float offset = 0.0;
uint32_t command_value = 0;
uint32_t frequency = 0;

typedef struct {
    size_t position;
    float value;
} ClosestResult;

ClosestResult findClosest(float* array, size_t size, float target);

void InputCommand(void) //Input command
{
    printf("Enter a command: ");
    scanf_s("%19s", command, (unsigned int)sizeof(command));

}

bool isNumber(const char* str) // Check for number
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (!isdigit(str[i]) && str[i] != '.') // Check if each character is a digit or a decimal point
            return false;
        i++;
    }
    return true;
}

void SCPI(char command[])
{

    

    for (int i = 0; command[i]; i++) //Convert to lower so commands are case insensitive
    {
        command[i] = tolower(command[i]);
    }

    if (strcmp(command, "meas:voltage:battery?") == 0 || strcmp(command, "measure:voltage:battery?") == 0 || strcmp(command, "meas:volt:battery?") == 0 || strcmp(command, "measure:volt:battery?") == 0)
    {
        printf("Battery voltage is: %.1f\n", batteryVoltage);
    }



    char* split; //Define split variable
    split = strtok(command, ":");

    if (split != NULL)
    { //Cycle through command & determine 2 parameters of each command, first is FREQ, WAVE or AMPL, second is either a numerical value (for freq,ampl) or sine, tria or square for waaveform type
        strcpy(command_type, split);

        split = strtok(NULL, ":");

        if (split != NULL)
        {
            if (strcmp(command_type, "freq") == 0 || strcmp(command_type, "frequency") == 0) //Frequency command & value assignment
            {
                if (isNumber(split)) // Check if the value is a number
                {
                    command_value = atoi(split);
                    frequency = command_value;

                    if (frequency < 1) //Limit checking
                    {
                        frequency = 1;
                        printf("Minimum frequency is 1 Hz\n");
                        printf("Frequency set to %lu\n", frequency);
                    }
                    else if (frequency > 12500000) //Limit checking 
                    {
                        frequency = 12500000;
                        printf("Maximum frequency is 12.5 MHz\n");
                        printf("Frequency set to %lu\n", frequency);
                    }
                    else
                    {
                        printf("Command Type: %s\n", command_type);
                        printf("Command Value: %d\n", command_value);
                        printf("Setting frequency to %lu\n", frequency);
                    }
                }
                else //In case where command value isnt a number
                {
                    printf("Please input a valid value\n");
                }
            }
            else if (strcmp(command_type, "wave") == 0 || strcmp(command_type, "waveform") == 0) //Waveform command & waveform type assigment 
            {
                strcpy(command_value_str, split);

                if (strcmp(command_value_str, "sine") == 0)
                {
                    strcpy(waveform, "SINE");
                    printf("Command Type: %s\n", command_type);
                    printf("Command Value: %s\n", command_value_str);
                    printf("Waveform: %s\n", waveform);
                }
                else if (strcmp(command_value_str, "tria") == 0)
                {
                    strcpy(waveform, "TRIANGLE");
                    printf("Command Type: %s\n", command_type);
                    printf("Command Value: %s\n", command_value_str);
                    printf("Waveform: %s\n", waveform);
                }
                else if (strcmp(command_value_str, "square") == 0)
                {
                    strcpy(waveform, "SQUARE");
                    printf("Command Type: %s\n", command_type);
                    printf("Command Value: %s\n", command_value_str);
                    printf("Waveform: %s\n", waveform);
                }
                else
                {
                    printf("Unsupported waveform, supported waveforms are sine, tria and square");
                }
            }
            else if (strcmp(command_type, "ampl") == 0 || strcmp(command_type, "amplitude") == 0) //Amplitude command & amplitude assigment
            {

                if (isNumber(split)) // Check if the value is a number
                {
                    amplitude = atof(split);
                    ClosestResult result = findClosest(amplitudeArray, sizeof(amplitudeArray) / sizeof(amplitudeArray[0]), amplitude);
                    amplitude = result.value;
                    printf("Closest value is: %.2f\n", result.value);
                    printf("Position in the array: %lu\n", result.position);
                    if (amplitude > 12) //Limit checking
                    {
                        amplitude = 12;
                        printf("Maximum amplitude is 12.00 Vpp\n");
                        printf("Amplitude set to %.2f Vpp\n", amplitude);
                    }
                    else if (amplitude <= 0)
                    {
                        amplitude = 0.0;
                        printf("Minimum amplitude is 0.2 Vpp\n");
                        printf("Amplitude set to %.2f Vpp\n", amplitude);
                    }
                    else
                    {
                        printf("Command Type: %s\n", command_type);
                        printf("Command Value: %s\n", split);
                        printf("Setting amplitude to %.2f\n", amplitude);
                    }

                }
                else //In case where command value isnt a number
                {
                    printf("Please input a valid value\n");
                }
            }
            else if (strcmp(command_type, "off") == 0 || strcmp(command_type, "offset") == 0) //Offset command & amplitude assigment
            {
                if (isNumber(split)) // Check if the value is a number
                {
                    offset = atof(split);

                    if (offset < -5) //Limit checking
                    {
                        offset = -5;
                        printf("Command Type: %s\n", command_type);
                        printf("Command Value: %s\n", split);
                        printf("Minimum offset is -5 V\n");
                        printf("Setting offset to %.2f\n", offset);
                    }
                    else if (offset > 5) //Limit checking 
                    {
                        offset = 5;
                        printf("Command Type: %s\n", command_type);
                        printf("Command Value: %s\n", split);
                        printf("Maximum offset is +5 V\n");
                        printf("Setting offset to %.2f\n", offset);
                    }
                    else
                    {
                        printf("Command Type: %s\n", command_type);
                        printf("Command Value: %s\n", split);
                        printf("Setting offset to %.2f\n", offset);
                    }
                }
                else //In case where command value isnt a number
                {
                    printf("Please input a valid value");
                }

            }
            else if (strcmp(command_type, "outp") == 0 || strcmp(command_type, "output") == 0) //Output control
            {
                strcpy(command_value_str, split);

                if (strcmp(command_value_str, "start") == 0)
                {
                    
                    printf("Output: ON");

                }
                else if (strcmp(command_value_str, "stop") == 0)
                {
                   
                    printf("Output: OFF");
                }
                else
                {
                    printf("Please input a valid command (START/STOP)");
                }
            }
            else if (strcmp(command_type, "res") == 0 || strcmp(command_type, "resistance") == 0) //Output impedance control
            {
                strcpy(command_value_str, split);

                if (strcmp(command_value_str, "highz") == 0)
                {

                    printf("Mode: HighZ");

                }
                else if (strcmp(command_value_str, "50") == 0)
                {

                    printf("Mode: 50 ohm");
                }
                else
                {
                    printf("Please input a valid command (50 ohm/ HighZ)");
                }
            }
            
        }
        else
        {
            printf("Unrecognized command");
        }
    }
}
#ifndef SCPI_H
#define SCPI_H

#include <stdbool.h>

bool isNumber(const char* str);
void SCPI(char command[]);
void InputCommand(void);

#endif

#include <stdio.h>
#include <stdlib.h>

#include "input.h"

char* getUserInput()
{
    size_t bufsize = 1024;
    char* buffer = malloc(bufsize);
    getline(&buffer, &bufsize, stdin);

    return buffer;
}
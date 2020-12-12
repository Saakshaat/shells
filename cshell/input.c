#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

char *getUserInput()
{
    size_t bufsize = 1024;
    char *buffer = malloc(bufsize);
    getline(&buffer, &bufsize, stdin);

    int length = strlen(buffer);

    if (buffer[length - 1] == '\n')
    { // delete new-line character
        buffer[length - 1] = '\0';
    }

    return buffer;
}
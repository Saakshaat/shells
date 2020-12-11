#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <libgen.h>

#include "input.h"

char *getCurrentDirectoryPath()
{
    char* cwd = getcwd(NULL, 0);
    if(cwd == NULL) {
        perror("failed to get current directory\n");
        exit(1);
    } else {
        return cwd;
    }
}

char *getConsolePrompt()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char *promptStr = malloc(64 * sizeof(char));
    char *currentDirectory = basename(getCurrentDirectoryPath());

    sprintf(promptStr, "%02d:%02d %s$ ", (int)tm.tm_hour, (int)tm.tm_min, currentDirectory);

    return promptStr;
}

char *getUserInput()
{
    return NULL;
}
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <libgen.h>

#include "display.h"

int getTerminalWidth(void)
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    return w.ws_col;
}

char *appendPipes(char *text)
{
    char *finalString = malloc(strlen(text) + 2);

    finalString[0] = '|';

    for (int i = 1; i < strlen(text) - 1; i++)
    {
        finalString[i] = text[i];
    }

    return finalString;
}

char *centerTextInPattern(char *text, int terminalWidth)
{
    int pad = (terminalWidth - strlen(text) - 2) / 2;

    char *leftPaddedStr = calloc(strlen(text) + pad + 1, sizeof(char));
    memset(leftPaddedStr, ' ', pad);
    strncpy(leftPaddedStr + pad, text, strlen(text));

    return appendPipes(leftPaddedStr);
}

char *fitPatternToWidth(int terminalWidth)
{
    char *patternStr = (char *)malloc(sizeof(terminalWidth));

    patternStr[0] = '/';
    for (int i = 1; i < terminalWidth; i++)
    {
        patternStr[i] = '*';
    }

    return patternStr;
}

void welcomeScreen()
{
    int terminalWidth = getTerminalWidth();

    printf("%s\n", fitPatternToWidth(terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("--", terminalWidth));
    printf("%s\n", centerTextInPattern("/    \\", terminalWidth));
    printf("%s\n", centerTextInPattern("|      |", terminalWidth));
    printf("%s\n", centerTextInPattern("|CSHELL|", terminalWidth));
    printf("%s\n", centerTextInPattern("|      |", terminalWidth));
    printf("%s\n", centerTextInPattern("\\    /", terminalWidth));
    printf("%s\n", centerTextInPattern("--", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("**SAAKSHAAT SINGH**", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", fitPatternToWidth(terminalWidth));
    printf("%s", "\n");
}

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
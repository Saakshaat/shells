#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "display.h"

int getTerminalWidth(void)
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    return w.ws_col;
}

char* appendPipe(char* text) {
    char* finalString = malloc(strlen(text) + 2);

    finalString[0] = '|';

    for(int i = 1; i < strlen(text) - 1; i++) {
        finalString[i] = text[i];
    }

    return finalString;
}

char* centerTextInPattern(char* text, int terminalWidth) {
        int pad = (terminalWidth-strlen(text) - 2)/2;

        char *leftPaddedStr = calloc(strlen(text) + pad + 1, sizeof(char));
        memset(leftPaddedStr, ' ', pad);
        strncpy(leftPaddedStr+pad, text, strlen(text));
        
        free(leftPaddedStr);

        return appendPipes(leftPaddedStr);
}

char* fitPatternToWidth(int terminalWidth) {
    char* patternStr = (char*)malloc(sizeof(terminalWidth));

    patternStr[0] = '/';
    for(int i = 1; i < terminalWidth ; i++) {
        patternStr[i] = '*';
    }

    return patternStr;
}

void welcomeScreen() {
    int terminalWidth = getTerminalWidth();

    printf("%s\n", fitPatternToWidth(terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("//WELCOME TO CSHELL\\\\", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("**SAAKSHAAT SINGH**", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", centerTextInPattern("", terminalWidth));
    printf("%s\n", fitPatternToWidth(terminalWidth));
    printf("%s", "\n");

}

// TODO: implement
char* getPrompt() {
    return NULL;
}
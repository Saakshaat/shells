#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "display.h"
#include "interpret.h"
#include "input.h"

void init() {
	welcomeScreen();
}

int main() {
	/**
	 * Steps for the shell to run:
	 * 1. Display prompt
	 * 2. Get user input (getline)
	 * 3. Parse input into tokens
	 * 4. Interpret tokens by aliases, builtins and paths to create an expression
	 * 5. Execute the command made from the expression
	 * 6. Repeat
	 * 
	 */
	init();

	// user input - this variable will be removed from the driver
	char * input;

	do {
		if(input[0] != '\0') { // if the input isn't empty, evaluate input
			interpretExpression(input, 3); // parsing, evaluation and execution will occure elsewhere
		}

		printf("%s", getConsolePrompt());
		scanf("%s", input); // a helper in another file will replace this and take care of parsing the entire line

	} while(input[0] != '\0' || input[0] != '\n' || strcmp(input,"^C") != 0 || strcmp(input,"^D") != 0); // FIXME: change to valid checks
	
	return 0;
}

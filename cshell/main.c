#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "interpret.h"

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
	printf("Welcome to cshell!\n"); // a function writing welcome to the console will replace this

	// user input - this variable will be removed from the driver
	char * input;

	do {
		if(input[0] != '\0') { // if the input isn't empty, evaluate input
			interpretExpression(input, 3); // parsing, evaluation and execution will occure elsewhere
		}

		printf("cshell>"); // a nicer prompt should replace this since `printf()` takes up memory itself
		scanf("%s", input); // a helper in another file will replace this and take care of parsing the entire line

	} while(input[0] != '\0' || input[0] != '\n' || strcmp(input,"^C") != 0 || strcmp(input,"^D") != 0); // FIXME: change to valid checks
	
	return 0;
}

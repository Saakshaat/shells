#include<stdio.h>
#include<stdlib.h>
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

	interpretExpression("line", 3);
	return 0;
}

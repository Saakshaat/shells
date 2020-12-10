#include<stdio.h>
#include<stdlib.h>
#include "interpret.h"

int main() {
	char* buffer;
	size_t bufsize = 32;
	size_t characters;

	buffer = (char*)malloc(bufsize * sizeof(char));

	if(buffer == NULL) {
		perror("Unable to allocate buffer.");
		exit(1);
	}

	printf("Type something:\n");
	characters = getline(&buffer, &bufsize, stdin);

	interpretExpression(buffer, 3);
	return 0;
}

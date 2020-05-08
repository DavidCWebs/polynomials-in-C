#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

// get user input:
// - A constant
// - Number of shares

void inputData(int *vars, size_t size)
{
	struct termios echoOrig, echoOff;
	tcgetattr(0, &echoOrig);
	echoOff = echoOrig;
	echoOff.c_lflag &= ~ECHO;

	char *inputs[] = {
		"Please enter the secret integer: ",
		"Please enter the required number of shares: ",
		"Please enter the threshold: "
	};

	char *line = NULL, *endptr;
	size_t len = 0;
	ssize_t lineSize = 0;
	for (size_t i = 0; i < sizeof(inputs) / sizeof(*inputs) || i < size; i++) {
		if (i == 0) tcsetattr(0, TCSANOW, &echoOff);
		if (i == 1) tcsetattr(0, TCSANOW, &echoOrig);
		printf("%s\n", inputs[i]);
		lineSize = getline(&line, &len, stdin);
		if (lineSize == 0) {
			fprintf(stderr, "getline() failed.\n");
			exit(EXIT_FAILURE);
		}
		vars[i] = strtol(line, &endptr, 10);
	}
	free(line);
}


int main()
{
	int vars[3];
	inputData(vars, 3);
	printf("The secret is: %d\n", vars[0]);
	return 0;
}

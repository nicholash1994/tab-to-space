#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    This program takes in a string as input, and outputs a string where
    the tabs are replaced by a specified number of spaces. The first argument
    to the program should be the number of spaces to replace each tab with.
    The second argument should be the input string. If more than 2 arguments
    are given, the first will be used as the number of spaces per tab, the
    second will be used as the input string, and the rest of the arguments will
    be ignored.

    Example: tab-to-space 4 "Detab this    string"
*/

void print_usage_err();
void detab_string(const char* input_string, const int s_num);
void detab_file(const char* filename, const int s_num);

int main(int argc, char** argv) {
	int s_num; // number of spaces

	//  these if statements process the command-line arguments
	if (argc == 1 || argc == 2) {
		print_usage_err();
		return -1;
	}
	s_num = atoi(argv[1]);
	if (s_num <= 0 || s_num > 8) {
		printf("Error: The number of spaces per tab must be between 1 and 8.\n");
		return -1;
	}
	if (strcmp("-f", argv[2]) == 0)
		detab_file(argv[3], s_num);
	else
		detab_string(argv[2], s_num);

	return 0;
}

void print_usage_err() {
	printf("Usage: ./tab-to-space n string\n");
	printf("  OR   ./tab-to-space n -f filename\n\n");
	printf("Example: ./tab-to-space n \"This is a string\t with a tab.\"\n");
}

void detab_string(const char* input_string, const int s_num) {
	char* output_string;
	int len, i, j;

	len = strlen(input_string);
	output_string = (char*)malloc((s_num*len+1)*sizeof(char));

	j = 0;
	for (i = 0; i < len; i++) {
		if (input_string[i] == '\t') {
			memset(output_string+j, ' ', s_num*sizeof(char));
			j += s_num;
		}
		else {
			output_string[j] = input_string[i];
			j++;
		}
	}
	output_string[j] = '\0';

	printf("%s\n", output_string);

	free(output_string);
}

void detab_file(const char* filename, const int s_num) {
	FILE* file;
	char in_buffer[32];
	//char* out_buffer = (char*)malloc(s_num*32*sizeof(char));
	int i, j, bytes;

	if ((file = fopen(filename, "r")) == NULL) {
		printf("Error: file couldn't be opened!\n");
		exit(-1);
	}

	j = 0;
	while (1) {
		bytes = fread(in_buffer, sizeof(char), 32, file);
		if (ferror(file)) {
			printf("Error while reading file!\n");
			exit(-1);
		}
		for (i = 0; i < bytes; i++)
			if (in_buffer[i] == '\t')
				for (j = 0; j < s_num; j++)
					putchar(' ');
			else
				putchar(in_buffer[i]);
		if (feof(file))
			break;
	}

	if (fclose(file)) {
		printf("Error while attempting to close file!\n");
		exit(-1);
	}
}

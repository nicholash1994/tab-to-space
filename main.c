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

int main(int argc, char** argv) {
    int i, j;
    int s_num; // number of spaces
    int len; // length of input string
    char* input_string;
    char* output_string;

    if (argc == 1) {
        printf("Usage: ./tab-to-space n string\n");
        printf("Example: ./tab-to-space n \"This is a string\t with a tab.\"\n");
        return -1;
    }
    else if (argc == 2) {
        printf("Only 1 argument given! Defaulting to 4 spaces per tab!\n");
        s_num = 4;
        input_string = argv[1];
    }
    else {
        input_string = argv[2];
        s_num = atoi(argv[1]);
        if (s_num > 8) {
            printf("Error: Number of tabs cannot exceed 8!\n");
            return -1;
        }
    }
    if (s_num <= 0) {
        printf("Error: the number of spaces must be positive!\n");
        return -1;
    }

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

    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Opens a file named input.txt for reading and a file named      *
 *              output a file named output.txt for writing, and outputs        *
 *              in the latter all words from the former form last to first.    *
 *                                                                             *
 * Written by Eric Martin and Xi Zhang(3472528) for COMP9021                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(void) {
    FILE *input_file = fopen("input.txt", "r");
    if (!input_file) {
        printf("Please create a file named \"input.txt\""
               " in the working directory.\n");
        return EXIT_FAILURE;
    }
    FILE *output_file = fopen("output.txt", "w");
    long count, length;
    int count_letter = 0, ch;
    fseek(input_file, 0L, SEEK_END);
    length = ftell(input_file);
    for (count = 1L; count <= length; ++count) {
        fseek(input_file, -count, SEEK_END);
        ch = getc(input_file);
        if (isalpha(ch))
            count_letter++;
        else if (count_letter) {
                for (int i = 0; i < count_letter; ++i)
                    fprintf(output_file, "%c", ch = getc(input_file));
                fprintf(output_file, "\n");
                count_letter = 0;
        }
    }
    if (count_letter) {
        for (int i = 0; i < count_letter; ++i) {
            fprintf(output_file, "%c", ch);
            ch = getc(input_file);
        }
        fprintf(output_file, "\n"); 
    }
    fclose(input_file);
    fclose(output_file);
    return EXIT_SUCCESS;
}
 
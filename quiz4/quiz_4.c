/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Reads a line of input and transforms it in some way...         *
 *                                                                             *
 * Written by Eric Martin and Xi Zhang(z3472528) for COMP9021                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
int main(void) {
    int largest_digit = 0;
    char beginning_of_word[8];
    int minimal_length = 0;
    bool fully_processed_previous_word = true;
    int word_length = 0;
    int c;
    while ((c = getchar()) != '\n') {
        int only_space;   //A switch which is used to test if there are space after a word and before a punctuation.
        int a;
        if (c >= '0' && c <= '9')
            a = 1;
        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            a = 2;
        else
            a = 3;
        switch (a){
            case 1:    //if c is a number.
                if (only_space == 1){
                    word_length = 0;
                    printf(".\n");
                    only_space = 0;
                }
                if (word_length){
                    printf(".\n");
                    word_length = 0;
                    largest_digit = c - '0';
                    continue;
                }
                else{
                    if ((c - '0') > largest_digit)
                        largest_digit = c - '0';
                    minimal_length = largest_digit;
                    continue;
                }
            case 2:    //if c is a letter.
                largest_digit = 0;
                if (only_space == 1){
                    word_length = 0;
                    printf(".\n");
                    only_space = 0;
                }
                if (word_length != 0 && fully_processed_previous_word == true){
                    if (c >= 'a' && c <= 'z')
                        printf("%c", c);
                    if (c >= 'A' && c <= 'Z')
                        printf("%c", c + 32);
                    word_length++;
                    continue;
                }
                else{
                    if (c >= 'a' && c <= 'z')
                        beginning_of_word[word_length] = c;
                    if (c >= 'A' && c <= 'Z')
                        beginning_of_word[word_length] = c + 32;
                    word_length++;
                    if (word_length < minimal_length){
                        fully_processed_previous_word = false;
                        continue;
                    }
                    else{
                        for (int i = 0; i < word_length; ++i)
                            printf("%c", beginning_of_word[i]);
                        fully_processed_previous_word = true;
                        continue;
                    }
                    continue;
                }
            case 3:    //if c is a punctuation.
                if (word_length >= minimal_length && word_length != 0){
 
                    if (c != ' '){
                        printf("%c\n", c);
                        word_length = 0;
                        only_space = 0;
                        continue;
                    }
                    else{
                        only_space = 1;
                        continue;
                    }
                }
                else if (word_length < minimal_length && word_length != 0){
                    minimal_length = 0;
                    word_length = 0;
                    continue;
                }
                else{
                    word_length = 0;
                    continue;
                }
        }
    }
    if (word_length && word_length >= minimal_length)
        printf(".\n");
    return EXIT_SUCCESS;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Keeps only digits and stores them in reverse order             *
 *              in the reordered command line arguments, where the             *
 *              first one remains first, the second one becomes last,          *
 *              the third one becomes second, the fourth one becomes           *
 *              penultimate, etc.                                              *
 * Written by Xi Zhang(3472528) for COMP9021                                   *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       quiz7.c                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include <ctype.h>
#include <string.h>
 
void process_command_line_arguments(char **argv, int argc) {
    /*Here I use a array to contain the original argv for later use.*/
    char *ar[argc-1];
    for (int i = 1; i < argc; ++i) {
        ar[i] = argv[i]; //initialize ar[] by giving it the string of argv[] one by one.
        char *p = argv[i];
        int length = strlen(argv[i]); // get the length of a string.
        char *q = argv[i]+length -1;
        /*Here I reverse the sequence of every string in argv by change reversing their address by two pointers*/
        for (int j = 1; j <= (length+1)/2 ; ++j) {
            char temp = *p;
            *p = *q;
            *q = temp;
            p++;
            q--;
        }
        char digit[length]; //create a array to contain the digits of each string.
        int count_digit = 0;
        /*Here I initialize array digit[] by giving each of char a 0. Then I move every digit appearing in argv[i]
         * into digit[], and eventually give the saved digits back to argv by ending with 0.*/
        for (int j = 0, k = 0; j < length; ++j) {
            digit[j] = 0;
            if (isdigit(argv[i][j])) {
                count_digit++;
                digit[k++] = argv[i][j];
            }
        }
/*renew the array digit[],if not doing so when the number of digits containing in the preceding string is bigger
 * then that in the current string, the exceeding length of digits in the formal string will be output again.*/
        for (int j = 0; j < length; ++j) {
            argv[i][j] = digit[j];
            digit[j] = 0;
        }
    }
    /*Here I shuffle the strings as required.*/
    for (int i = 1; i < argc; ++i) {
        if (i % 2 == 1)
            argv[(i +1)/2] = ar[i];
        if (!(i % 2))
            argv[argc - i/2] = ar[i];
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: - Prompts the user for a nonnegative number n at most equal    *
 *              to 1023, encoding a set S of digits,                           *
 *              - prompts the user for an integer impetus, and                 *
 *              - shifts the members of S impetus times to the right or to     *
 *              the left depending on whether impetus is positive or negative, *
 *              respectively, and looping around (so 9 shifted to the right    *
 *              once becomes 0, and 0 shifted to the left once becomes 9).     * 
 *                                                                             *
 * Written by Eric Martin and *** for COMP9021                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 
#define MAX 1023
 
int shift(int, int);
void display_set_coded_by(int);
 
int main(void) {
    int n;
    do {
        printf("Enter a nonnegative number at most equal to %d: ", MAX);
        rewind(stdin);
    } while ((!scanf("%d", &n) || n < 0 || n > MAX) && !fflush(stdin));
    int impetus;
    printf("Enter an integer: ");
    scanf("%d", &impetus);
    printf("Shifting through ");
    display_set_coded_by(n);
    printf("\n         yields ");
    display_set_coded_by(shift(n, impetus));
    puts(".");
    return EXIT_SUCCESS;
}
 
void display_set_coded_by(int n) {
    putchar('{');
    bool digits_found = false;
    for (int i = 0; i < 10; ++i)
        if (n & 1 << i) {
            if (digits_found)
                printf(", ");
            printf("%d", i);
            digits_found = true;
        }
    putchar('}');
}
 
int shift(int n, int impetus) {
    int new_n = 0; //This is for the new n after shifting.
    int new_i;
 
    /*Changing i with impetus into new_i which could indicate the times for multipling 2.*/
    for (int i = 0; i < 10; ++i) {
        if (n & 1 << i) {
            new_i = (i + impetus + 10 - ((impetus / 10) - 1) * 10) % 10;
            int factor = 1; //the virable 'factor' collects the factors of new_n.
            for (int j = 1; j <= new_i; ++j)
                factor *= 2;
            new_n += factor;
        }
    }
    return new_n;
}

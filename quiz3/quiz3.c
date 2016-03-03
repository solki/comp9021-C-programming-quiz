/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for a floating point number in base 3         *
 *              represented as a dot                                           *
 *               - preceded by between 1 and 20 digits equal to 0, 1 or 2,     *
 *                 the first of which is not 0 and is possibly preceded by     *
 *                 + or -, and                                                 *
 *               - followed by between 0 and 10 digits equal to 0, 1 or 2.     *
 *               Outputs a representation of this number in base 10            *
 *               and in base 2.                                                *
 *                                                                             *
 * Written by Eric Martin and *** for COMP9021                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define MAX_SIZE 33
#define PRECISION 10 
 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(void) {
    printf("Enter a floating point number in base 3 represented as a dot\n"
           "- preceded by between 1 and 20 digits equal to 0, 1 or 2,\n"
           "the first of which is not 0 and is possibly preceded by + or -, and\n"
           "- followed by between 0 and 10 digits equal to 0, 1 or 2:\n");
    char characters[MAX_SIZE];
    int i = 0;
    int c;
    while ((c = getchar()) != '\n')
        characters[i++] = c;
    characters[i] = '\0';
    double number;
    char sign = '+';
    int exponent = 0;
    int mantissa[PRECISION] = {0};
    if (characters[0] == '+' || characters[0] == '-')
    {
        sign = characters[0]; 
        for (int i = 0; characters[i] != '\0'; ++i)
            characters[i] = characters[i+1];
    }
    int count_int = 0;
    int count_dec = 0;
    for (int i = 0; characters[i] != '.'; ++i)
        count_int++;
    for (int i = count_int + 1; characters[i] != '\0'; ++i)
        count_dec++;
    int integer[MAX_SIZE];
    int decimal[MAX_SIZE];
    for (int i = 0; i < count_int; ++i)
        integer[i] = characters[count_int - 1 - i] - '0';
    for (int i = 0; i < count_dec; ++i)
        decimal[i] = characters[count_int + 1 + i] - '0';
    int fact_int = 1;
    double fact_dec = 1.0 / 3.0;
    number = 0;
    for (int i = 0; i < count_int; ++i)
    {
        
        number = number + fact_int * integer[i];
        fact_int = fact_int * 3;
    }
    for (int i = 0; i < count_dec; ++i)
    {
        number = number + fact_dec * decimal[i];
        fact_dec = fact_dec / 3;
    }
    long int num = number;
    double dec = number - num;
    int a[40] = {0};
    int ct1 = 0;
    for (int i = 0; i < 40; ++i)
    {
        
        a[i] = num % 2;
        num = num / 2;
        ct1++;
        if (num == 0)
            break;
    }
    if (ct1 < 11)
    {
        for (int i = 0, j = ct1 - 2; i < ct1 - 1; ++i, --j)
            mantissa[i] = a[j];
        // int b[10]={0};
        for (int i = 0; i < 11 - ct1; ++i)
        {
            mantissa[i+ct1-1] = (int)(dec * 2.0);
            dec = dec * 2.0 - mantissa[i+ct1-1];
        }
    }
    else
        for (int i = 0, j = ct1 - 2; i < PRECISION; ++i, --j)
            mantissa[i] = a[j];
    exponent = ct1 - 1;
if (sign == '-')
        number = 0 - number;
    printf("The number that has been input is approximately equal to %f\n", number);
    printf("In base 2, this number is approximately equal to %c1.", sign);
    for (i = 0; i < PRECISION; ++i)
        if (mantissa[i])
            putchar('1');
        else
            putchar('0');
    printf(" * 2^%d\n", exponent);
    return EXIT_SUCCESS;
}
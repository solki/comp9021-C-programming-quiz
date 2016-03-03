#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define SIZE 10
#define BOUND 5
 
int main(int argc, char **argv) {
    /* We run the program with one number as command line argument. */
    if (argc != 2) {
        printf("Please provide 1 command line argument.\n");
        return EXIT_FAILURE;
    }
    /* We use it as a seed for the random number generator. */
      srand(strtoul(argv[1], NULL, 10));
      /* srand((unsigned)time(NULL));*/
    int data[SIZE];
    /* We randomly generate 10 numbers in the range [0, 5) and store them in data. */
    for (int i = 0; i < SIZE; ++i)
        data[i] = rand() % BOUND;
    int digit_count[BOUND] = {0};
    int nb_of_nonzero_digits;
    int least_frequent_digit = 0, most_frequent_digit = 0;
    
    /*We count the number of each digit and save them to array digit_count[].*/
 
    for (int i = 0; i < SIZE; ++i){
      for (int j = 0; j< BOUND; ++j){
	if (data[i] == j)
	  digit_count[j] += 1;
      }
    }
   
    /*We caculate the number of nonzero digits by using BOUND -(numbers of zero digits).*/
 
    nb_of_nonzero_digits = SIZE - digit_count[0];
   
    /*We define another array named a[] to repalce array digit_count[]. It's not necessary,but for the convenience of using afterwards.*/
    
    int a[BOUND];
    for (int i = 0; i < BOUND; ++i)
      a[i] = digit_count[i];
   
    int max = 0, min = SIZE;
    
    /*We find the largest nonzero least frequent digit.*/
 
    for (int i = 1; i < BOUND; ++i)
      if (min >= a[i] && a[i] != 0){
	least_frequent_digit = i;
	min = a[i];
      }   
    
    /*We find the smallest nonzero most frequent digit.*/
 
    for (int i = 1; i < BOUND; i++)
      if (max < a[i] && a[i] != 0){
	most_frequent_digit = i;
	max = a[i];
      }
             
    /*Here, for checking the value of each variable. 
      printf("%d %d\n", max, min);
      printf("%d %d %d %d\n", a[1],a[2],a[3],a[4]);
      printf("%d %d %d %d %d\n",digit_count[0],digit_count[1],digit_count[2],digit_count[3],digit_count[4]);*/
   
    printf("The digits that have been generated are: ");
    for (int i = 0; i < SIZE; ++i)
        printf("%2d", data[i]);
    putchar('\n'); /*same as printf("\n");*/
    if (!nb_of_nonzero_digits)
        printf(" All those digits are equal to 0.\n");
    else {
        printf(" %d of those digits", nb_of_nonzero_digits);
        nb_of_nonzero_digits == 1 ? printf(" is ") : printf(" are ");
        printf("not equal to 0.\n");
        printf(" The largest nonzero least frequent digit is %d\n", least_frequent_digit);
        printf(" The smallest nonzero most frequent digit is %d\n", most_frequent_digit);
    }   
    return EXIT_SUCCESS;
}
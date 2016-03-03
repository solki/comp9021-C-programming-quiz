/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Randomly fills an array of size 10x10 with 0s and 1s, and      *
 *              outputs the number of parallelograms with horizonatal sides.   *
 *                                                                             *
 * Written by Eric Martin and Xi Zhang(3472528) for COMP9021                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 
#define DIM 10
#define STRAIGHT 0
#define LEFT 1
#define RIGHT 2
 
bool grid[DIM][DIM];
 
void display_grid(void);
int size_of_largest_parallelogram(void);
/* If j1 < j2 and the grid has a 1 at the intersection of row i and column j
 * for all j in {j1, ..., j2}, then returns the side of the largest parallelogram
 * having this row of 1s as top side, and with vertical sides going down in 1 of 3 possible
 * directions as selected by dir. */
int size_of_largest_parallelogram_with_given_top_side(int i, int j1, int j2, int dir);
 
int main(int argc, char **argv) {
    /* We run the program with two command line arguments. */
    if (argc != 3) {
        printf("Please provide 2 command line arguments.\n");
        return EXIT_FAILURE;
    }
    /* The first one will determine our probability distribution;
     * it is meant to be nonzero. */
    int nb_of_possible_outcomes = strtol(argv[1], NULL, 10);
    if (!nb_of_possible_outcomes) {
        printf("The first command line argument should not be 0.\n");
        return EXIT_FAILURE;
    }
    /* We use the second command line argument, meant to be a nonnegative integer,
     * as a seed for the random number generator. */
    srand(strtoul(argv[2], NULL, 10));
    /* We fill the grid with randomly generated 0s and 1s,
     * with for every cell, a probability of 1/nb_of_possible_outcomes to generate a 0. */
    if (nb_of_possible_outcomes > 0)
        for (int i = 0; i < DIM; ++i)
            for (int j = 0; j < DIM; ++j)
                grid[i][j] = rand() % nb_of_possible_outcomes > 0;
    else {
        for (int i = 0; i < DIM; ++i)
            for (int j = 0; j < DIM; ++j)
                grid[i][j] = rand() % nb_of_possible_outcomes == 0;
    }   
    puts("Here is the grid that has been generated:\n");
    display_grid();
    int size = size_of_largest_parallelogram();
    if (size)
        printf("The largest parallelogram with horizontal sides has a size of %d.\n",
               size_of_largest_parallelogram());
    else
        printf("There is no parallelogram with horizontal sides.\n");
    return EXIT_SUCCESS;
}
 
void display_grid(void) {
    for (int i = 0; i < DIM; ++i) {
        printf("    ");
        for (int j = 0; j < DIM; ++j)
            printf(" %d", grid[i][j]);
        putchar('\n');
    }
    putchar('\n');
}
 
int size_of_largest_parallelogram(void) {
    int i1, j1, j2, dir;
    /*Here, I give a array to store the size calculated from 3 directions. If
     * there is no parallelogram can be found from some directions. Then the
     * result will be 0;*/
    int temp_size[3] = {0};
    int temp = 0;
    for (int i = 0; i < DIM - 1; ++i)
        for (int j = 0; j < DIM - 1; ++j)
        {
            if (grid[i][j] == 1)
            {
                i1 = i;
                j1 = j;
                for (int k = 1; k < DIM - j1; ++k)
                {
                    if (grid[i1][j1+k] == 0)
                    {
                        break;
                    }
                    if (grid[i1][j1+k] == 1)
                    {
                        j2 = j1 + k;
                        if (grid[i1+1][j1] == 1)
                        {
                            dir = 0;
                            temp_size[0] = size_of_largest_parallelogram_with_given_top_side(i1, j1, j2, dir);
                        }
                        if (grid[i1+1][j1-1] == 1)
                        {
                            dir = 1;
                            temp_size[1] = size_of_largest_parallelogram_with_given_top_side(i1, j1, j2, dir);
                        }
                        if (grid[i1+1][j1+1] == 1)
                        {
                            dir = 2;
                            temp_size[2] = size_of_largest_parallelogram_with_given_top_side(i1, j1, j2, dir);
                        }
                        for (int m = 0; m < 3; ++m)
                        {
                            if (temp_size[m] > temp)
                            {
                                temp = temp_size[m];
                                temp_size[m] = 0;
                            }
                            continue;   
                        }
                    }
                }
            }
        }
    return temp;               
}
 
int size_of_largest_parallelogram_with_given_top_side(int i1, int j1, int j2, int dir) {
    /*Here, I use variable 'count' to count the number of consecutive 1s appearing in the route of
     * scanning parallelogram line by line. And at each end of one line. I check if the count result
     * is equal to the ideal one which is the long side times the number of lines. If not stop the
     * loop and return the count result in a proper form.*/
    int count = 0;
    switch (dir)
    {
        case STRAIGHT:
            for (int i = i1; i < DIM; ++i)
            {
                if (count == (i - i1) * (j2 - j1 + 1))
                {
                    for (int j = j1; j <= j2; ++j)
                    {
                        if (grid[i][j] == 1)
                            count++;
                    }
                }
                else
                {
                    count = (i - i1 - 1) * (j2 - j1 + 1);
                    break;
                }
            }
            if (count < 2 * (j2 - j1 + 1))
                count = 0;
            break;
        case LEFT:
            for (int i = i1; i < DIM; ++i)
            {
                if (count == (i - i1) * (j2 - j1 + 1))
                {
                    for (int j = (j1 - i + i1); j <= (j2 - i + i1) && j >= 0; ++j)
                    {
                        if (grid[i][j] == 1)
                            count++;
                    }
                }
                else
                {
                    count = (i - i1 - 1) * (j2 - j1 + 1);
                    break;
                }
            }
            if (count < 2 * ( j2 - j1 + 1))
                count = 0;
            break;
        case RIGHT:
            for (int i = i1; i < DIM; ++i)
            {
                if (count == (i - i1) * (j2 - j1 + 1))
                {
                    for (int j = (j1 + i - i1); j <= (j2 + i - i1) && j < DIM; ++j)
                    {
                        if (grid[i][j] == 1)
                            count++;
                    }
                }
                else
                {
                    count = (i - i1 - 1) * (j2 - j1 + 1);
                    break;
                }
            }
            if (count < 2 * (j2 - j1 + 1))
                count = 0;
            break;
    }
    return count;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes +s and digits as command line arguments, checks whether  *
 *              they make up a valid infix expression, and evaluates it        *
 *              in case it is.                                                 *
 *                                                                             *
 * Written by   Xi Zhang  for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_stack.c                                                      *
 *       quiz10.c                                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
/* THIS IS THE ONLY FILE YOU HAVE TO SUBMIT.
 * IT WILL BE COMPILED WITH THE OTHER FILES YOU HAVE BEEN PROVIDED WITH. */
 
#include "my_code.h"
 
void store_command_line_args_in_stack(int argc, char **argv, Stack *const pt_to_stack) {
    for (int i = 1; i < argc; ++i) {
        if (*argv[i] >= '0' && *argv[i] <= '9')
            push(*argv[i] - '0', pt_to_stack);
        else
            push(*argv[i], pt_to_stack);
    }
}
 
bool is_correct_prefix_expression(Stack *const pt_to_stack) {
    long int count_number = 0;
    long int count_operator = 0;
    Value val;
    while (pt_to_stack->height) {
        pop(pt_to_stack, &val);
        if (val >= 0 && val <= 9)
            count_number++;
        else
            count_operator++;
        if (count_operator >= count_number)
            return false;
    }
    if (count_operator != count_number - 1)
        return false;
    else
        return true;
}
 
Value evaluate_expression(Stack *const pt_to_stack) {
    Value sum = 0;
    Value val;
    while (pt_to_stack->height) {
        pop(pt_to_stack, &val);
        if (val >= 0 && val <= 9)
            sum += val;
    }
    return sum;
}
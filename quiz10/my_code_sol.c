/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Keeps only digits and stores them in reverse order             *
 *              in the reordered command line arguments, where the             *
 *              first one remains first, the second one becomes last,          *
 *              the third one becomes second, the fourth one becomes           *
 *              penultimate, etc.                                              *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       quiz7.c                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <string.h>

void process_command_line_arguments(char **argv, int argc) {
    char *reordered_argv[argc];
    int step = 1;
    for (int i = 1; i <= argc / 2; ++i, step += 2)
        reordered_argv[i] = argv[step];
    step = 2;
    for (int i = 1; i <= (argc - 1) / 2; ++i, step += 2)
        reordered_argv[argc - i] = argv[step];
    for (int i = 1; i < argc; ++i)
        argv[i] = reordered_argv[i];
    for (int i = 1; i < argc; ++i) {
        int length = strlen(argv[i]);
        char number_extracted[length];
        int j = 0;
        for (int k = 0; k < length; ++k)
            if (isdigit(argv[i][k]))
                number_extracted[j++] = argv[i][k];
        int k = 0;
        while (j)
            argv[i][k++] = number_extracted[--j];
        argv[i][k] = '\0';
    }
}

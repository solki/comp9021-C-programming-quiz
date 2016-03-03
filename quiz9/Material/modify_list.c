/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes as command line argument a nonnegative int N followed    *
 *              by at least N+1 characters, builds a linked list from these    *
 *              characters, and modifies this list so that it starts with the  *
 *              (N+1)st node A and is followed by every second node, moving    *
 *              backwards and wrapping around, followed by the node preceding  *
 *              A again followed by every second node, moving backwards and    *
 *              wrapping around.                                               *
 *                                                                             *
 * Written by Xi Zhang(3472528) for COMP9021                                   *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_list.c                                                       *
 *       quiz9.c                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
/* THIS IS THE ONLY FILE YOU HAVE TO SUBMIT.
 * IT WILL BE COMPILED WITH THE OTHER FILES YOU HAVE BEEN PROVIDED WITH. */
 
#include "modify_list.h"
 
void modify_list(Node **const pt_to_pt_to_node, const int starting_point) {
    Node *pt_to_node = *pt_to_pt_to_node;
    Node *copy_pt_to_node = duplicate_list(pt_to_node);
    reverse_list(&copy_pt_to_node);
    Node *pt_to_first_original_node = pt_to_node;
    Node *pt_to_first_node = copy_pt_to_node;
    long int length = list_length(copy_pt_to_node);
    for (long int i = 0L; i < length - 1; ++i)
        copy_pt_to_node = copy_pt_to_node->pt_to_next_node;
    copy_pt_to_node->pt_to_next_node = pt_to_first_node;
    copy_pt_to_node = pt_to_first_node;
    for (long int i = 1L; i < length - starting_point; ++i)
        copy_pt_to_node = copy_pt_to_node->pt_to_next_node;
    for (long int i = 0L; i < length; ++i) {
        while (copy_pt_to_node->value == '\0')
            copy_pt_to_node = copy_pt_to_node->pt_to_next_node;
        pt_to_node->value = copy_pt_to_node->value;
        if (pt_to_node->pt_to_next_node)
            pt_to_node = pt_to_node->pt_to_next_node;
        else
            pt_to_node = pt_to_first_original_node;
        copy_pt_to_node->value = '\0';
        copy_pt_to_node = copy_pt_to_node->pt_to_next_node;
        copy_pt_to_node = copy_pt_to_node->pt_to_next_node;
    }
    *pt_to_pt_to_node = pt_to_node;
}
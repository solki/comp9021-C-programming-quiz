/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes as command line argument a nonnegative int N followed    *
 *              by at least N+1 characters, builds a linked list from these    *
 *              characters, and modifies this list so that it starts with the  *
 *              (N+1)st node A and is followed by every second node, moving    *
 *              backwards and wrapping around, followed by the node preceding  *
 *              A again followed by every second node, moving backwards and    *
 *              wrapping around.                                               *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_list.c                                                       *
 *       quiz9.c                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "modify_list.h"

void modify_list(Node **const pt_to_pt_to_node, const int starting_point) {
    Node *pt_to_node = *pt_to_pt_to_node;
    const int length = list_length(pt_to_node);
    Node *pt_to_nodes[length];
    for (int i = 0; i < length; ++i) {
        pt_to_nodes[i] = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    pt_to_node = pt_to_nodes[starting_point];
    *pt_to_pt_to_node = pt_to_node;
    for (int n = 0; n < 2; ++n) {
        int i;
        if (n)
            i = starting_point - 1;
        else
            i = starting_point;
        if (n && i >= 0) {
            pt_to_node->pt_to_next_node = pt_to_nodes[i];
            pt_to_node = pt_to_node->pt_to_next_node;
        }   
        while (i > 1) {
            pt_to_node->pt_to_next_node = pt_to_nodes[i - 2];
            pt_to_node = pt_to_node->pt_to_next_node;
            i -= 2;
        }
        if (i)
            i = length - 1;
        else
            i = length - 2;
        if (i > starting_point) {
            pt_to_node->pt_to_next_node = pt_to_nodes[i];
            pt_to_node = pt_to_node->pt_to_next_node;
        }
        while (i > starting_point + 2) {
            pt_to_node->pt_to_next_node = pt_to_nodes[i - 2];
            pt_to_node = pt_to_node->pt_to_next_node;
            i -= 2;
        }
    }
    pt_to_node->pt_to_next_node = NULL;
}


#ifndef NODE_HPP
#define NODE_HPP

#include "token.hpp"

enum node_type {
    //enum used to label node by type
    program_node, block_node, vars_node, expr_node, n_node, a_node, m_node, r_node, stats_node, mstat_node, stat_node, in_node, out_node, if_node, loop_node, assign_node, ro_node, label_node, goto_node
};

struct tree_node 
{

    //holds the tokens and children of any given node
    /* data */
    node_type label;
    token token1;
    token token2;
    token token3;
    tree_node *child1;
    tree_node *child2;
    tree_node *child3;
    tree_node *child4;
    tree_node *child5;
};


#endif
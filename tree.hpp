#ifndef TREE_HPP
#define TREE_HPP

#include "token.hpp"
#include "node.hpp"

tree_node* generate_node(node_type);
void pre_order_traversal(tree_node*, int);
void print_tabs(int);
void print_node(tree_node*, int);

#endif
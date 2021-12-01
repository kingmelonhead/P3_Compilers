#ifndef SEMANTICS_HPP
#define SEMANTICS_HPP

#include "token.hpp"
#include "tree.hpp"
#include <vector>
#include <string>

void semantics(tree_node *);
void traverse(tree_node *);
void get_vars(tree_node *, int &);
void not_dec(std::string);
void double_dec(std::string);
void visit_block(tree_node *);
void push(std::string);
void pop();
int find(std::string, int);

#endif
#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"
#include "node.hpp"
#include <string>

tree_node* Parser();
tree_node* PROGRAM();
tree_node* BLOCK();
tree_node* VARS();
tree_node* EXPR();
tree_node* N();
tree_node* A();
tree_node* M();
tree_node* R();
tree_node* STATS();
tree_node* MSTAT();
tree_node* STAT();
tree_node* IN();
tree_node* OUT();
tree_node* IF();
tree_node* LOOP();
tree_node* ASSIGN();
tree_node* RO();
tree_node* LABEL();
tree_node* GOTO();
void error(tokenID, tokenID);
void print(std::string);
#endif
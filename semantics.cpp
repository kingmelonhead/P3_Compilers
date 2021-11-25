#include "semantics.hpp"
#include <stack>



void semantics(tree_node * root){
    std::stack<token> * vars;

    //visit the vars node to get the global vars
    get_globals(root->child1, vars);

    left_right_trav(root->child1, vars); // start traversal in the program block
    
}

void left_right_trav(tree_node * root, std::stack<token> * variables){
    //find var blocks, push to stack when declared, pop from stack when leaving scope
    

}

void get_globals(tree_node * n, std::stack<token> * variables){
    //goes through the first var block to get any globals that may exist
}

void not_dec(){
    //identifier tries to be used but it has not been declared in the current scope
}

void double_dec(){
    //identifier tries to be declared but it has alredy been declared in the current scope
}
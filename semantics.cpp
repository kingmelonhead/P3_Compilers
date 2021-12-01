#include "semantics.hpp"
#include <iostream>

std::vector<std::string> vars;
int global_count = 0;

bool debug = true;

void semantics(tree_node * root){
    //the driver function that gets called from the main cpp file
    get_vars(root->child1, global_count);  // visit the vars node to get the global vars
    visit_block(root->child2);  // start traversal in the program block
}

void visit_block(tree_node * n){
    //this function is used when a new block is discovered
    int varCount = 0;
    get_vars(n->child1, varCount);
    if (n->child2 != NULL) traverse (n->child2);
    for (int i = 0; i < varCount; i++) pop();
}

void traverse(tree_node * n){
    //find var blocks, push to stack when declared, pop from stack when leaving scope
    if (n->label == block_node) visit_block(n);
    else {
        if (n->token1.token_type == ID_Token){
            int temp = find(n->token1.token_string, 0);
            if (temp == -1) not_dec(n->token1.token_string);
        }

        if (n->token2.token_type == ID_Token){
            int temp = find(n->token2.token_string, 0);
            if (temp == -1) not_dec(n->token2.token_string);
        }

        if (n->token3.token_type == ID_Token){
            int temp = find(n->token3.token_string, 0);
            if (temp == -1) not_dec(n->token3.token_string);
        }
        if (n->child1 != NULL) traverse(n->child1);
        if (n->child2 != NULL) traverse(n->child2);
        if (n->child3 != NULL) traverse(n->child3);
        if (n->child4 != NULL) traverse(n->child4);
        if (n->child5 != NULL) traverse(n->child5);
    }
}

void get_vars(tree_node * n, int & count){
    //goes through the first var block to get any globals that may exist
    if (n->token1.token_type != ID_Token) return;
    int temp = find(n->token1.token_string, count);
    if (temp == -1){
        push(n->token1.token_string);
        count++;
    }
    else double_dec(n->token1.token_string);
    if (n->child1 != NULL) get_vars(n->child1, count);
}

void not_dec(std::string str){
    //identifier tries to be used but it has not been declared in the current scope
    std::cout << "ERROR: " << str << " has been referenced but has not yet been declared in the current scope. Exiting program...\n";
    exit(0);
}

void double_dec(std::string str){
    //identifier tries to be declared but it has alredy been declared in the current scope
    std::cout << "ERROR: " << str << " has been declared already in the current scope. Exiting program...\n";
    exit(0);
}

void stack_overflow(){
    //too many variables have been declared
    std::cout << "ERROR: stack has reached 100 vars, program will now exit...\n";
    exit(0);
}

void push(std::string str){
    //pushes an ID to the stack
    if (vars.size() == 100) stack_overflow();
    if (debug) std::cout << "DEBUG: pushing " << str << "\n";
    vars.push_back(str);
}

void pop(){
    //removes the top ID from the stack
    if (debug) std::cout << "DEBUG: popping.\n";
    vars.pop_back();
}

int find(std::string str, int stop){
    //look through all variables
    for (int i = vars.size() -1; i >= stop; i--){
        if (vars.at(i) == str){
            if (debug) std::cout << "DEBUG: " << str << " has been found in vars\n";
            return (vars.size() - 1) - i;
        } 
    }
    return -1;
}
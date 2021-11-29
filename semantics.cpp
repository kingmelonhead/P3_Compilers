#include "semantics.hpp"
#include <iostream>

std::vector<std::string> vars;

void semantics(tree_node * root){
    get_globals(root->child1);  // visit the vars node to get the global vars
    visit_block(root->child2);  // start traversal in the program block
}

void traverse(tree_node * n){
    //find var blocks, push to stack when declared, pop from stack when leaving scope
    if (n->label == block_node) visit_block(n);
    else {
        if (n->child1 != NULL) traverse(n->child1);
        if (n->child2 != NULL) traverse(n->child2);
        if (n->child3 != NULL) traverse(n->child3);
        if (n->child4 != NULL) traverse(n->child4);
        if (n->child5 != NULL) traverse(n->child5);

        if (n->token1.token_type == ID_Token){
            int temp = find(n->token1.token_string);
            if (temp == -1) not_dec(n->token1.token_string);
        }

        if (n->token2.token_type == ID_Token){
            int temp = find(n->token2.token_string);
            if (temp == -1) not_dec(n->token2.token_string);
        }

        if (n->token3.token_type == ID_Token){
            int temp = find(n->token3.token_string);
            if (temp == -1) not_dec(n->token3.token_string);
        }
    }
}

void get_globals(tree_node * n){
    //goes through the first var block to get any globals that may exist
    if (n->token1.token_type != ID_Token) return;
    int temp = find(n->token1.token_string);
    if (temp == -1){
        vars.push_back(n->token1.token_string);
        std::cout << n->token1.token_string << " is being pushed to global vars\n";
    } 
    else {
        std::cout << "in get_globals(): ";
        double_dec(n->token1.token_string);
    }
    if (n->child1 != NULL) get_globals(n->child1);
    return;
}

void get_locals(tree_node * n, int & count){
    //goes through the first var block to get any globals that may exist
    if (n->token1.token_type != ID_Token) return;
    int temp = find_locals(n->token1.token_string, count);
    if (temp == -1){
        push(n->token1.token_string);
        count++;
    }
    else {
        std::cout << "in get_locals(): ";
        double_dec(n->token1.token_string);
    } 
    if (n->child1 != NULL) get_locals(n->child1, count);
    return;
}

void not_dec(std::string str){
    //identifier tries to be used but it has not been declared in the current scope
    std::cout << "ERROR: " << str << " has been referenced but has not yet been declared in the current scope. Exiting program...\n";
    exit(0);
    return;
}

void double_dec(std::string str){
    //identifier tries to be declared but it has alredy been declared in the current scope
    std::cout << "ERROR: " << str << " has been declared already in the current scope. Exiting program...\n";
    exit(0);
    return;
}

void visit_block(tree_node * n){
    int varCount = 0;
    get_locals(n->child1, varCount);
    if (n->child2 != NULL) traverse (n->child2);
    for (int i = 0; i < varCount; i++) pop();
}

void push(std::string str){
    std::cout << "DEBUG: pushing " << str << "\n";
    vars.push_back(str);
    return;
}

void pop(){
    std::cout << "DEBUG: popping.\n";
    vars.pop_back();
    return;
}

int find(std::string str){
    //look through locals
    for (int i = vars.size() -1; i >= 0; i--){
        if (vars.at(i) == str){
            std::cout << "DEBUG: " << str << " has been found in vars\n";
            return (vars.size() - 1) - i;
        } 
    }
    return -1;
}

int find_locals(std::string str, int count){
    for (int i = vars.size() - 1; i >= (vars.size() - count); i--){
                if (vars.at(i) == str){
            std::cout << "DEBUG: " << str << " has been found in vars\n";
            return (vars.size() - 1) - i;
        } 
    }
    return -1;
}


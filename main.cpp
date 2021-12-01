#include "scanner.hpp"
#include "parser.hpp"
#include "testScanner.hpp"
#include "tree.hpp"
#include "node.hpp"
#include "semantics.hpp"
#include <iostream>

void print_arg_error();

int main(int argc, char *argv[]){

    std::string filename = "";

    tree_node *tree_root;

    if (argc == 1) driver(filename, KEYBOARD);
    else if (argc == 2) driver(argv[1], SOURCE_FILE);
    else print_arg_error();

    std::cout << "Scanner Finished!\n";

    tree_root = Parser();

    std::cout << "Parser Finished!\n";
    
    //pre_order_traversal(tree_root, 0); //this is the printing 
    
    semantics(tree_root);

    std::cout << "Static Semantics Finished!\n";

    //code generation will go here
    return 0;
}

void print_arg_error(){
    std::cout << "Error: There is either too many, or too few arguments.\n invoke program using './P1 filename'\n";
    exit(0);
}
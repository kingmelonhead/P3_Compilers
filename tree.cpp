#include "tree.hpp"
#include "token.hpp"
#include <string>
#include <iostream>

tree_node* generate_node(node_type ndType){
    tree_node *temp = new tree_node();
    temp->label = ndType;
    temp->token1 = {.token_type = WHITESPACE, .token_string = "", .line_no = 0};
    temp->token2 = {.token_type = WHITESPACE, .token_string = "", .line_no = 0};
    temp->token3 = {.token_type = WHITESPACE, .token_string = "", .line_no = 0};
    temp->child1 = NULL;
    temp->child2 = NULL;
    temp->child3 = NULL;
    temp->child4 = NULL;
    temp->child5 = NULL;
    return temp;
}

void pre_order_traversal(tree_node* n, int depth){

    if (n != NULL){
        print_node(n, depth);
        pre_order_traversal(n->child1, depth +1);
        pre_order_traversal(n->child2, depth +1);
        pre_order_traversal(n->child3, depth +1);
        pre_order_traversal(n->child4, depth +1);
        pre_order_traversal(n->child5, depth +1);
    }
}

void print_node(tree_node* n, int depth){
    /*
    enum node_type {
    program_node, block_node, vars_node, expr_node, n_node, a_node, m_node, r_node, stats_node, mstat_node, stat_node, in_node, out_node, if_node, loop_node, assign_node, ro_node, label_node, goto_node
    };
    */

   std::string names[] = {"whitespace", "Identifier", "Number", "Assignment Opperator", "Comparison Opperator", "Greater Than", "Less Than", "Colon", "Define Op (:=)", "Add", "Subtract", "Multiply", 
                            "Divide", "Percent", "Period", "Opening Parenthesis", "Closing Parenthesis", "Comma", "Opening Curley Brace", "Closing Curly Brace", "Semi-colon",
                            "Opening Square Brace", "Closing Square Brace", "start", "stop", "loop", "while", "for", "label", "exit", "listen", "talk",  "program", 
                            "if", "then", "assign", "declare", "jump", "else", "EOF"};

    std::string labels[] = {"<program>", "<block>", "<vars>", "<expr>", "<n>", "<a>", "<m>", "<r>", "<stats>", "<mstat>", "<stat>", "<in>", "<out>", "<if>", "<loop>", "<assign>", "<ro>", "<label>", "<goto>"};

    print_tabs(depth);

    std::cout << labels[n->label] << std::endl;

    if (n->token1.token_type != WHITESPACE){
        print_tabs(depth);
        std::cout << "|Token 1: {" << names[n->token1.token_type] << ", " << n->token1.token_string << ", Line: " << n->token1.line_no << " }\n";
    }

    if (n->token2.token_type != WHITESPACE){
        print_tabs(depth);
        std::cout << "|Token 2: {" << names[n->token2.token_type] << ", " << n->token2.token_string << ", Line: " << n->token2.line_no << " }\n";
    }

    if (n->token3.token_type != WHITESPACE){
        print_tabs(depth);
        std::cout << "|Token 3: {" << names[n->token3.token_type] << ", " << n->token3.token_string << ", Line: " << n->token3.line_no << " }\n";
    }
}

void print_tabs(int depth){
    for (int i = 0; i < depth; i++){
        std::cout << "  ";
    }
}
#include "parser.hpp"
#include "token.hpp"
#include "scanner.hpp"
#include "tree.hpp"
#include "node.hpp"
#include <iostream>

static token current_tk;

// just used for error messages
std::string TKNames[] = {"whitespace", "Identifier", "Number", "Assignment Op (=)", "Comparison Op (==)", "Greater Than", "Less Than", "Colon", "Define Op (:=)", "Add", "Subtract", "Multiply", 
                            "Divide", "Percent", "Period", "Opening Parenthesis", "Closing Parenthesis", "Comma", "Opening Curley Brace", "Closing Curly Brace", "Semi-colon",
                            "Opening Square Brace", "Closing Square Brace", "start", "stop", "loop", "while", "for", "label", "exit", "listen", "talk",  "program", 
                            "if", "then", "assign", "declare", "jump", "else", "EOF"};

//NOTE: any time Scanner is called, it is just getting the next token from the scanner
//putting this here instead of putting the same comment above ever call to the scanner

//all the functions in this file that return pointers to nodes are different parts of the grammar, and the functions are designed to effectively check tokens from 
//the scanner against what would be in a follow set, and throws an error if an invalid token is encountered
//putting this here because all of the functions do the same thing, just for different parts of the language

//the function names indicate the part of the parse tree they are responsible for

tree_node* Parser(){

    tree_node *root;

    current_tk = Scanner();
    root = PROGRAM();

    if (current_tk.token_type != EOF_Token) error(EOF_Token, current_tk.token_type);

    std::cout << "Parser finished!\n";
    return root;
}

tree_node* PROGRAM(){

    tree_node *temp = generate_node(program_node);

    temp->child1 = VARS();

    if (current_tk.token_type != program_tk) error(program_tk, current_tk.token_type);

    current_tk = Scanner();
    temp->child2 = BLOCK();

    print("program validated");
    return temp;
}

tree_node* BLOCK(){

    tree_node *temp = generate_node(block_node);

    if (current_tk.token_type != start_tk) error(start_tk, current_tk.token_type);

    current_tk = Scanner();
    temp->child1 = VARS();
    temp->child2 = STATS();

    if (current_tk.token_type != stop_tk) error(stop_tk, current_tk.token_type);
    
    current_tk = Scanner();
    
    print("block validated");
    return temp;
}

tree_node* VARS(){

    tree_node *temp = generate_node(vars_node);

    if (current_tk.token_type == declare_tk){
    
        current_tk = Scanner();

        if (current_tk.token_type != ID_Token) error(ID_Token, current_tk.token_type);
        
        temp->token1 = current_tk;
        current_tk = Scanner();

        if (current_tk.token_type != Ass_Token) error(Ass_Token, current_tk.token_type);
               
        current_tk = Scanner();

        if (current_tk.token_type != Num_Token) error(Num_Token, current_tk.token_type);
        
        temp->token2 = current_tk;
        current_tk = Scanner();

        if (current_tk.token_type != Semi_Token) error(Semi_Token, current_tk.token_type);
                  
        current_tk = Scanner();
        temp->child1 = VARS();
    }
    
    print("vars validated");
    return temp;
    
}

tree_node* EXPR(){

    tree_node *temp = generate_node(expr_node);

    temp->child1 = N();

    if (current_tk.token_type == Plu_Token){
        temp->token1 = current_tk;
        current_tk = Scanner();
        temp->child2 = EXPR();
    }
    print("expression validated");
    return temp;
}   

tree_node* N(){

    tree_node *temp= generate_node(n_node);

    temp->child1 = A();

    if (current_tk.token_type == Div_Token || current_tk.token_type == Mult_Token){
        temp->token1 = current_tk;
        current_tk = Scanner();
        temp->child2 = N();
    } 
    print("n validated");
    return temp;
}

tree_node* A(){

    tree_node *temp = generate_node(a_node);

    temp->child1 = M();

    if (current_tk.token_type == Min_Token){
        temp->token1 = current_tk;
        current_tk = Scanner();
        temp->child2 = A();
    }
    print("a validated");
    return temp;
}

tree_node* M(){

    tree_node *temp = generate_node(m_node);

    if (current_tk.token_type == Dot_Token){
        temp->token1 = current_tk;
        current_tk = Scanner();
        temp->child1 = M();
    }
    else temp->child1 = R();

    print("m validated");
    return temp;
}

tree_node* R(){

    tree_node *temp = generate_node(r_node);

    if (current_tk.token_type == LParen_Token){

        current_tk = Scanner();
        temp->child1 = EXPR();

        if (current_tk.token_type != RParen_Token) error(RParen_Token, current_tk.token_type);

        current_tk = Scanner();
    }
    else if (current_tk.token_type == ID_Token){

        temp->token1 = current_tk;
        current_tk = Scanner();
    }
    else if (current_tk.token_type == Num_Token){

        temp->token1 = current_tk;
        current_tk = Scanner();
    }
    else {
        print("was expecting ( <expr> ) | Identifier | Integer but got " + TKNames[current_tk.token_type]);
    }

    print("r validated");
    return temp;
}

tree_node* STATS(){

    tree_node *temp = generate_node(stats_node);
  
    temp->child1 = STAT();
    temp->child2 = MSTAT();

    print("stats validated");
    return temp;
}

tree_node* MSTAT(){

    tree_node *temp = generate_node(mstat_node);

    if (current_tk.token_type == listen_tk || current_tk.token_type == talk_tk || current_tk.token_type == if_tk 
        || current_tk.token_type == start_tk || current_tk.token_type == while_tk || current_tk.token_type == assign_tk 
        || current_tk.token_type == jump_tk || current_tk.token_type == label_tk){
        temp->child1 = STAT();
        temp->child2 = MSTAT();
    }
    print("mstat validated");
    return temp;
}

tree_node* STAT(){

    tree_node *temp = generate_node(stat_node);

    if (current_tk.token_type == listen_tk) temp->child1 = IN();
    else if (current_tk.token_type == talk_tk) temp->child1 = OUT();
    else if (current_tk.token_type == start_tk) temp->child1 = BLOCK();
    else if (current_tk.token_type == if_tk) temp->child1 = IF();
    else if (current_tk.token_type == while_tk) temp->child1 = LOOP();
    else if (current_tk.token_type == assign_tk) temp->child1 = ASSIGN();
    else if (current_tk.token_type == jump_tk) temp->child1 = GOTO();
    else if (current_tk.token_type == label_tk) temp->child1 = LABEL();
    else {
        print("error in STAT(): expecting { listen | talk  | start | if  | while | declare | jump | label } but got " + TKNames[current_tk.token_type]);
        exit(0);
    }

    print("stat validated");
    return temp;
}

tree_node* IN(){

    tree_node *temp = generate_node(in_node);

    if (current_tk.token_type != listen_tk) error(listen_tk, current_tk.token_type);

    current_tk = Scanner();

    if (current_tk.token_type != ID_Token) error(ID_Token, current_tk.token_type);
    
    temp->token1 = current_tk;
    current_tk = Scanner();

    if (current_tk.token_type != Semi_Token) error(Semi_Token, current_tk.token_type);
    
    current_tk = Scanner();
    
    print("in validated");
    return temp;

}

tree_node* OUT(){

    tree_node *temp = generate_node(out_node);

    if (current_tk.token_type != talk_tk) error(talk_tk, current_tk.token_type);

    current_tk = Scanner();
    temp->child1 = EXPR();

    if (current_tk.token_type != Semi_Token) error(Semi_Token, current_tk.token_type);
      
    current_tk = Scanner();

    print("out validated");
    return temp;
}

tree_node* IF(){

    tree_node *temp = generate_node(if_node);

    if (current_tk.token_type != if_tk) error(if_tk, current_tk.token_type);

    current_tk = Scanner();

    if (current_tk.token_type != LSqBra_Token) error(LSqBra_Token, current_tk.token_type);
 
    current_tk = Scanner();

    temp->child1 = EXPR();
    temp->child2 = RO();
    temp->child3 = EXPR();

    if (current_tk.token_type != RSqBr_Token) error(RSqBr_Token, current_tk.token_type);
           
    current_tk = Scanner();

    if (current_tk.token_type != then_tk) error(then_tk, current_tk.token_type);
              
    current_tk = Scanner();
    temp->child4 = STAT();

    if (current_tk.token_type == else_tk){
                    
        current_tk = Scanner();
        temp->child5 = STAT();
    }

    if (current_tk.token_type != Semi_Token) error(Semi_Token, current_tk.token_type);
     
    current_tk = Scanner();

    print("if validated");
    return temp;
}

tree_node* LOOP(){

    tree_node *temp = generate_node(loop_node);

    if (current_tk.token_type != while_tk) error(while_tk, current_tk.token_type);

    current_tk = Scanner();

    if (current_tk.token_type != LSqBra_Token) error(LSqBra_Token, current_tk.token_type);

    current_tk = Scanner();
    temp->child1 = EXPR();
    temp->child2 = RO();
    temp->child3 = EXPR();

    if (current_tk.token_type != RSqBr_Token) error(RSqBr_Token, current_tk.token_type);
          
    current_tk = Scanner();
    temp->child4 = STAT();

    if (current_tk.token_type != Semi_Token) error(Semi_Token, current_tk.token_type);
    
    current_tk = Scanner();

    print("loop validated");
    return temp;
}

tree_node* ASSIGN(){

    tree_node *temp = generate_node(assign_node);

    if (current_tk.token_type != assign_tk) error(assign_tk, current_tk.token_type);

    current_tk = Scanner();

    if (current_tk.token_type != ID_Token) error(ID_Token, current_tk.token_type);
    
    temp->token1 = current_tk;
    current_tk = Scanner();

    if (current_tk.token_type != Ass_Token) error(Ass_Token, current_tk.token_type);
    
    current_tk = Scanner();
    temp->child1 = EXPR();

    if (current_tk.token_type != Semi_Token) error(Semi_Token, current_tk.token_type);
      
    current_tk = Scanner();

    print("assign validated");
    return temp;
}

tree_node* RO(){

    tree_node *temp = generate_node(ro_node);

    if (current_tk.token_type == Less_Token){

        temp->token1 = current_tk;
        current_tk = Scanner();
    }
    else if (current_tk.token_type == Greater_Token){

        temp->token1 = current_tk;
        current_tk = Scanner();
    }
    else if (current_tk.token_type == Comp_Token){

        temp->token1 = current_tk;
        current_tk = Scanner();
    }
    else if (current_tk.token_type ==  LCur_Token){

        temp->token1 = current_tk;

        current_tk = Scanner();

        if (current_tk.token_type != Comp_Token) error(Comp_Token, current_tk.token_type);

        temp->token2 = current_tk;
    
        current_tk = Scanner();

        if (current_tk.token_type != RCur_Token) error(RCur_Token, current_tk.token_type);

        temp->token3 = current_tk;
        
        current_tk = Scanner();
    
    }
    else if (current_tk.token_type == Perc_Token){

        temp->token1 = current_tk;
        current_tk = Scanner();
    }
    else {
        print("expected { >  | < |  ==  |   { == } | '%' } and got " + TKNames[current_tk.token_type]);
        exit(0);
    }

    print("ro validated");
    return temp;
}

tree_node* LABEL(){

    tree_node *temp = generate_node(label_node);

    if (current_tk.token_type != label_tk) error(label_tk, current_tk.token_type);

    current_tk = Scanner();

    if (current_tk.token_type != ID_Token) error(ID_Token, current_tk.token_type);
    
    temp->token1 = current_tk;
    current_tk = Scanner();

    if (current_tk.token_type != Semi_Token) error(Semi_Token, current_tk.token_type);

    current_tk = Scanner();

    print("label validated");
    return temp;
}

tree_node* GOTO(){
    
    tree_node *temp = generate_node(goto_node);

    if (current_tk.token_type != jump_tk) error(jump_tk, current_tk.token_type);

    current_tk = Scanner();

    if (current_tk.token_type != ID_Token) error(ID_Token, current_tk.token_type);
    
    temp->token1 = current_tk;
    current_tk = Scanner();

    if (current_tk.token_type != Semi_Token) error(Semi_Token, current_tk.token_type);
  
    current_tk = Scanner();

    print("goto validated");
    return temp;
}

void error(tokenID expected, tokenID got){
    std::cout << "Error: Parser recieved token of type: " << TKNames[got] << " but epected token of type: " << TKNames[expected] << std::endl;
    exit(0);
}

void print(std::string text){

    //print function used for debugging, commented out to disable it
    //std::cout << text << std::endl;
    return;
}

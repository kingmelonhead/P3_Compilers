#include "testScanner.hpp"
#include "scanner.hpp"
#include <iostream>

std::string keywords[] = {}; 

std::string tokenNames[] = {"whitespace", "Identifier", "Number", "Assignment Op (=)", "Comparison Op (==)", "Greater Than", "Less Than", "Colon", "Define Op (:=)", "Add", "Subtract", "Multiply", 
                            "Divide", "Percent", "Period", "Opening Parenthesis", "Closing Parenthesis", "Comma", "Opening Curley Brace", "Closing Curly Brace", "Semi-colon",
                            "Opening Square Brace", "Closing Square Brace", "start", "stop", "loop", "while", "for", "label", "exit", "listen", "talk",  "program", 
                            "if", "then", "assign", "declare", "jump", "else", "EOF"};



void testScanner(){
    token temp;

    while (1){
        temp =  Scanner();
        if (temp.token_type == EOF_Token){
            std::cout << "end of file\n";
            break;
        }
        else {
            std::cout << tokenNames[temp.token_type] << std::endl;
        }
    }

}
#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <fstream>
#include <vector>
#include "token.hpp"

#define KEYWORD_COUNT 16
#define MAX_ID_LEN 8
#define SOURCE_FILE 2
#define KEYBOARD 1

struct container {
    std::string filter = "";
    int line_no = -1;
    bool end_of_file = false;
};
void print_vector(std::vector<token> &);
container refresh_filter(std::fstream &, int &, bool &);
void driver(std::string, int);
void print_file_error(std::string);
bool all_ws(std::string);
bool is_keyword(std::string);
void remove_comments(std::string &, bool &);
void early_exit();
void open_file(std::string);
int get_col(char, int, int); 

tokenID which_keyword(std::string);

token Scanner(); 

#endif
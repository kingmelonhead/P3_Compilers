#include "scanner.hpp"
#include "token.hpp"
#include <iostream>

std::fstream in_file;
int input;
static std::vector<token> tokens;
static int currrent_token = 0;

token Scanner(){
    //std::cout << "Scanner: " << tokens.at(currrent_token).token_string << std::endl;
    return tokens.at(currrent_token++);
}

void driver(std::string filename, int mode){

    const int state_no = 23;
    const int col_no = 25;
    const int ERROR = -1;
    const int FINAL = 100;
    int char_count;

    input = mode;

    int FSA_Table[state_no][col_no] = {
        //               a-z     A-Z      0-9     $     =       >      <      :     +       -      *      /      %      .      (      )      ,      {      }      ;      [     ]     WS     EOF   OTHER
        /* s1  WS */ {   s2,   ERROR,    s3,     s2,    s4,    s6,    s7,    s8,   s10,   s11,   s12,   s13,   s14,   s15,   s16,   s17,   s18,   s19,   s20,   s21,   s22,   s23,    s1, FINAL, ERROR},
        /* s2  ID */ {   s2,      s2,    s2,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s3 NUM */ {FINAL,   FINAL,    s3,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s4   = */ {FINAL,   FINAL, FINAL,  FINAL,    s5, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s5  == */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s6   > */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s7   < */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s8   : */ {FINAL,   FINAL, FINAL,  FINAL,    s9, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s9  := */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s10  + */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s11  - */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s12  * */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s13  / */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s14  % */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s15  . */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s16  ( */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s17  ) */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s18  , */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s19  { */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s20  } */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s21  ; */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s22  [ */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
        /* s23  ] */ {FINAL,   FINAL, FINAL,  FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, ERROR},
    };

    bool open_comment = false;
    std::string temp_string = "";
    token temp_token;
    container filter_data;
    int filter_len, state, look_ahead, current_column, line_no = 0;

    if (input == SOURCE_FILE) open_file(filename);   
    else std::cout << "You have chosen to use keyboard input. To signal EOF use ctrl + D on a new line.\n";                                             //open file, or at least try to

    while (!filter_data.end_of_file){
        filter_data = refresh_filter(in_file, line_no, open_comment);                 //this gets a line from file that needs to be converted to tokens
        filter_len = filter_data.filter.length();       
        //std::cout << "filter:" + filter_data.filter << std::endl;
        //std::cout << "filter length: " + filter_len << std::endl;
        if (!filter_data.end_of_file) {                                 //in here, each filter will be broken into individual tokens and stored in a vector
            state = s1;
            temp_string = "";
            char_count = 0;
            for (int i = 0; i <= filter_len - 1; i++){     
                char_count++;             //iterate over the filter, all logic for tokenization goes in here
                current_column = get_col(filter_data.filter[i], line_no, char_count);
                look_ahead = FSA_Table[state][current_column];
                if (look_ahead == ERROR){                               //the character being evaluated here would lead to an error state, ie. we dont have a state that can deal with it
                    std::cout << "ERROR: Token can not begin with '" << filter_data.filter[i] << "'\nexiting program....\n";
                    early_exit();
                }
                else if (look_ahead == FINAL || (temp_string.length() == MAX_ID_LEN && tokenID(state) == ID_Token)){        
                    //this character leads to a state that signals the previous working token is ready to be cut off, or that we need to manually cut it off because it is longer than 8 characters long
                    if (is_keyword(temp_string)) tokens.emplace_back(gen_token(temp_string, line_no, which_keyword(temp_string)));
                    else tokens.emplace_back(gen_token(temp_string, line_no, tokenID(state)));
                    temp_string = "";
                    state = s1;
                    look_ahead = FSA_Table[state][current_column];
                    if (look_ahead == ERROR){                           //after finalizing the token, after re evaluiating the character, it leads to an error state
                        std::cout << "ERROR: Token can not begin with '" << filter_data.filter[i] << "'\nexiting program....\n";
                        early_exit();
                    }
                    if (current_column != ws) temp_string += filter_data.filter[i];
                    if (look_ahead != FINAL) state = look_ahead;        //if the future state isnt a final state, we can move to that state for the next iteration
                }
                else {                                                  //here the character leads to neiter a final or error state so the character is simply appended to the working token, if its not white space, which it shouldnt be regardless
                    if (current_column != ws) temp_string += filter_data.filter[i];
                    state = look_ahead;                                 //move to the next state, this is safe because the program reaching this line indicates that
                }
            }
            if (temp_string != ""){                                     //if there is characters in the working token then turn it to a token
                if (is_keyword(temp_string)) tokens.emplace_back(gen_token(temp_string, line_no, which_keyword(temp_string)));
                else tokens.emplace_back(gen_token(temp_string, line_no, tokenID(state)));
            }
        }
    }
    //toss end of file token in there
    tokens.emplace_back(gen_token("", ++line_no, EOF_Token));
    //-------- TOKENS SHOULD BE READY FOR THE PARSER AS OF NOW -----------------//
    if (input == SOURCE_FILE) in_file.close();
    std::cout << std::endl;

    //print_vector(tokens);

    return;
}

void open_file(std::string filename){
    //attempt to open file
    in_file.open(filename, std::fstream::in);

    //if file cant open, then it doesnt exist
    if(!in_file.is_open()) {
        in_file.close();
        print_file_error(filename);
    }
}

token gen_token(std::string text, int line_no, tokenID kind){
    //generates token and returns it, uses info passed to fill the fields
    token temp;
    temp.line_no = line_no;
    temp.token_string = text;
    temp.token_type = kind;
    return temp;
}

void print_file_error(std::string filename){
    //prints an error if file cant open
    std::cout << "Error: The provided file " << filename << " does not exist in the current directory.\nExiting Program...\n";
    early_exit();
}

void print_vector(std::vector<token> &v){

    std::string tokenNames[] = {"whitespace", "Identifier", "Number", "Assignment Op (=)", "Comparison Op (==)", "Greater Than", "Less Than", "Colon", "Define Op (:=)", "Add", "Subtract", "Multiply", 
                            "Divide", "Percent", "Period", "Opening Parenthesis", "Closing Parenthesis", "Comma", "Opening Curley Brace", "Closing Curly Brace", "Semi-colon",
                            "Opening Square Brace", "Closing Square Brace", "start", "stop", "loop", "while", "for", "label", "exit", "listen", "talk",  "program", 
                            "if", "then", "assign", "declare", "jump", "else", "EOF"};
    //loop through vector
    for (int i = 0; i < v.size(); i++){
        //pull next element from vector
        token temp = v.at(i);
        //display token information to console
        std::cout << "('" << temp.token_string << "', line: " << temp.line_no << ", type: " << tokenNames[temp.token_type] << ")\n";

    }
}

container refresh_filter(std::fstream &infile, int &line_no, bool & open_comment){
    //function to keep pulling lines from file until line isnt all white space after removing comments
    container temp;
    while (1){
        if (input == SOURCE_FILE) {
            if (std::getline(infile, temp.filter)){     // gets line if not EOF
                line_no++; 
                temp.line_no = line_no; 
                remove_comments(temp.filter, open_comment);           // attempt to remove comments
                if (!all_ws(temp.filter)) break;        // if filter is not empty after removing comments then filter is good           
            }
            else {                                      // end of file is reached
                temp.end_of_file = true;
                break;
            }
        }
        else { // keyboard input
            std::cout << "Line " << line_no + 1 << ":";
            if (std::getline(std::cin, temp.filter)){     // gets line if not EOF
                line_no++; 
                temp.line_no = line_no; 
                temp.filter += " ";
                remove_comments(temp.filter, open_comment);           // attempt to remove comments
                if (!all_ws(temp.filter)) break;        // if filter is not empty after removing comments then filter is good           
            }
            else {                                      // end of file is reached
                temp.end_of_file = true;
                break;
            }
        }
        
    }
    return temp;
}

bool all_ws(std::string text){
    //function that determines if a string is all white space
    int len = text.length();
    if (len == 0) return true;
    for (int i = 0; i < len ; i++) if (text[i] != ' ') return false;
    return true;
}

void remove_comments(std::string &text, bool & open_comment){
    // function to remove comments from the filter, will recursively call itself after removing comments
    // this is to ensure full removal of comments even if there are multiple comments embeded on a single line
    int len = text.length();
    int open_com = -10, close_com = -10;
    if (all_ws(text)) return;
    if (!open_comment){                                 // if there is not currently open comments
        for (int i = 0; i <= len - 2; i++){             // iterate through string
            if (text[i] == '&' && text[i+1] == '&'){    // && detected
                if (i != open_com + 1){                 // && detected is new
                    if (open_com > -10){                // if open comment has been detected already
                        close_com = i+1;
                        text.erase(open_com, (close_com - open_com) + 1); 
                        remove_comments(text, open_comment);
                        return;
                    }
                    else open_com = i;                  // open coment is made
                }
            }
        }  
        //code reaches here if it gets through the whole loop without a completed embeded comment
        if (open_com > -1){                             // comment started this line but not closed
            text.erase(open_com, (len - open_com)); 
            open_comment = true;
            return;
        }
    }
    else {                                               // there is an open comment already
        if (len == 1) {                                  // if there is only one character then its impossible to close the comment on this line
            text = ""; 
            return;
        }
        for (int i = 0; i <= len - 2; i++){
            if (text[i] == '&' && text[i+1] == '&'){
                text.erase(0, i + 2);
                open_comment = false;
                remove_comments(text, open_comment);
                return;
            }
        }
        //if code gets all the way through that loop without hiting a close symbol and there is an open comment then just delete the ehole thing
        text = "";
    }
}

void early_exit() {
    //something went wrong so cleanup and exit
    if (in_file.is_open()) in_file.close();
    exit (0);
}

int get_col(char c, int line_no, int char_count){
    std::map <char, columns> m = {
        {'a',low}, {'b',low}, {'c',low}, {'d',low}, {'e',low}, {'f',low}, {'g',low}, {'h',low}, {'i',low}, {'j',low}, {'k',low}, {'l',low}, {'m',low},
        {'n',low}, {'o',low}, {'p',low}, {'q',low}, {'r',low}, {'s',low}, {'t',low}, {'u',low}, {'v',low}, {'w',low}, {'x',low}, {'y',low}, {'z',low},
        {'A', up}, {'B', up}, {'C', up}, {'D', up}, {'E', up}, {'F', up}, {'G', up}, {'H', up}, {'I', up}, {'J', up}, {'K', up}, {'L', up}, {'M', up}, 
        {'N', up}, {'O', up}, {'P', up}, {'Q', up}, {'R', up}, {'S', up}, {'T', up}, {'U', up}, {'V', up}, {'W', up}, {'X', up}, {'Y', up}, {'Z', up}, 
        {'0', num}, {'1', num}, {'2', num}, {'3', num}, {'4', num}, {'5', num}, {'6', num}, {'7', num}, {'8', num}, {'9', num}, 
        {'$', dol}, {'=', eq}, {'<', lt}, {'>', gt}, {':', col}, {'+', plu}, {'-', sub}, {'*', mul}, {'/', divi}, {'%', perc}, {'.', dot}, {'(', lper}, 
        {')', rper}, {',', com}, {'{', lcur}, {'}', rcur}, {';', sem}, {'[', lsq}, {']', rsq}, {' ', ws}
    };
    //this function checks to see if the current char is in our vocab
    auto temp = m.find(c);
    if (temp == m.end()){
        //char isnt found
        std::cout << "ERROR: " << c << " on line " << line_no << " at position " << char_count << " is not a valid symbol\nExiting program...\n";
        early_exit();
    }
    else {
        //char is found and its associated column # for the FSA is returned
        return temp->second;
    }
    //something terribly wrong and unexpected happens if code makes it to this return statement
    return -1;
}

bool is_keyword(std::string text){
    std::string keywords[] = {"start", "stop", "loop", "while", "for", "label", "exit", "listen", "talk", "program", "if", "then", "assign", "declare", "jump", "else"};  
    //loop through collection of keywords
    for (int i = 0; i < KEYWORD_COUNT; i++){
        //if passed string matches one of the keywords then return true
        if (text == keywords[i]) return true;
    }
    //otherwise it isnt a keyword
    return false;
}

tokenID which_keyword(std::string s){
    std::string keywords[] = {"start", "stop", "loop", "while", "for", "label", "exit", "listen", "talk", "program", "if", "then", "assign", "declare", "jump", "else"};
    for (int i = 0; i < KEYWORD_COUNT; i++){
        //if passed string matches one of the keywords then return true
        if (s == keywords[i]) return tokenID(i + 23);
    }
    std::cout << "Something messed up in which_keyword, exiting...\n";
    early_exit();
    return EOF_Token;
}
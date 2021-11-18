#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <map>

enum tokenID {WHITESPACE, ID_Token, Num_Token, Ass_Token, Comp_Token, Greater_Token, Less_Token, 
                Col_Token, Def_Token, Plu_Token, Min_Token, Mult_Token, Div_Token, 
                Perc_Token, Dot_Token, LParen_Token, RParen_Token, Com_Token, LCur_Token, 
                RCur_Token, Semi_Token, LSqBra_Token, RSqBr_Token, start_tk, 
                stop_tk, loop_tk, while_tk, for_tk, label_tk, exit_tk,
                listen_tk, talk_tk, program_tk, if_tk, then_tk, assign_tk,
                declare_tk, jump_tk, else_tk, EOF_Token};

struct token { 
    tokenID token_type;
    std::string token_string; 
    int line_no;
    };

token gen_token(std::string, int, tokenID);

enum columns {low, up, num, dol, eq, gt, lt, col, plu, sub, mul, divi, perc, dot, lper, rper, com, lcur, rcur, sem, lsq, rsq, ws, end, junk};

enum states {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20, s21, s22, s23};          

#endif
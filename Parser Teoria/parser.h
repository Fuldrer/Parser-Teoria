#ifndef _PARSER_H
#define _PARSER_H

#include "lexer.h"
#include <exception>

class Parser {
public:
    Parser(Lexer& lexer): lexer(lexer) {}
    void prog();
    void optional_func_dec();
    void func_head();
    void func_name();
    void func_type();
    void func_modifiers();
    void func_mods();
    void decl_type();
    void param_list_opt();
    void param_list();
    void param_list_p();
    void decl_param();
    void body();
    void stmt_list();
    void stmts();
    void stmt();
    void stmt_p();
    void compound_stmt();
    void while_stmt();
    void while_test();
    void if_stmt();
    void if_conds();
    void if_cond();
    void else_stmt();
    void else_r();
    void expr_stmt();
    void asg_stmt();
    void return_stmt();
    void bool_expr();
    void expr();
    void simple_expr();
    void term();
    void factor();
    void constant();
    void field();
    void qualifier();
    void eval();
    void eval_name();
    void par_list();
    void prm_list();
    void function();

        
private:
    Lexer& lexer;
    Token token;
};
#endif
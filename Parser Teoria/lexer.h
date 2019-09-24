#ifndef _LEXER_H
#define _LEXER_H
#include <iostream>
#include <cctype>
#include <stdlib.h>

enum class Token {
    ID,
    ADD_OP,
    MULT_OP,
    LOG_OP,
    REL_OP,
    ASIG,
    PERIOD,
    DDPERIOD,
    INCR,
    INT_LITERAL,
    FALSE_LITERAL,
    TRUE_LITERAL,
    REAL_LITERAL,
    STRING_LITERAL,
    DATE_LITERAL,
    /////////
    WHILE,
    IF,
    ELSE,
    RETURN,
    INICIO,
    IF_THEN,
    DO,
    END,
    //////////
    STATIC_TKN,
    //////////
    INT_TYPE,
    ANYTYPE_TYPE,
    BOOLEAN_TYPE,
    VOID_TYPE,
    REAL_TYPE,
    STRING_TYPE,
    DATE_TYPE,
    DIGIT,
    LETTER,
    BRACES_OP,
    BRACES_END,
    SEMICOLON,
    PAR_OP,
    PAR_END,
    COMA,
    /////////
    ERROR,
    Eof
};

class Lexer {
public:
    Lexer(std::istream &in): in(in) {}
    ~Lexer() {}

    Token getNextToken();
    std::string getText() { return text; }

private:
    std::istream &in;
    std::string text;
};
#endif

#include "lexer.h"
#include <string.h>

std::string keyword[18] = {"false","true","while","if","else","EXIT","BEGIN","THEN","DO",
                            "END","static","int","anytype","boolean","void","real","String","date"};

Token Lexer::getNextToken() 
{
    char symbol = in.get();
    text = "";
    while(true)
    {
        if(symbol == ' ' || symbol == '\t' || symbol == '\n' || symbol == '\r')
        {
            symbol = in.get();
            continue;
        }
        switch (symbol)
        {
            case '+': 
                text += symbol;
                symbol = in.get();
                if(symbol == '+'){
                    text+= symbol;
                    return Token::INCR;
                }
                else
                {
                    in.unget();
                    return Token::ADD_OP;
                }
            case '-': text += symbol; return Token::ADD_OP;
            case '*': text += symbol; return Token::MULT_OP;
            case '.': text += symbol; return Token::PERIOD;
            case '{': text += symbol; return Token::BRACES_OP;
            case '}': text += symbol; return Token::BRACES_END;
            case ';': text += symbol; return Token::SEMICOLON;
            case ',': text += symbol; return Token::COMA;
            case '/': 
                symbol = in.get();
                if(symbol == '/')
                {
                    symbol = in.get();
                    while (symbol != '\n')
                        symbol = in.get();
                    break;
                }
                else
                {
                    text += '/';
                    in.unget();
                    return Token::MULT_OP;
                }
            case '|': 
                text += symbol; 
                symbol = in.get(); 
                if(symbol == '|'){
                    text +=symbol;
                    return Token::LOG_OP; 
                }
                else
                    return Token::ERROR;
            case '&': 
                text += symbol;
                symbol = in.get();
                if(symbol == '&')
                {
                    text +=symbol;
                    return Token::LOG_OP; 
                }
                else
                    return Token::ERROR;
            case '>': 
                text += symbol; 
                symbol = in.get(); 
                if(symbol == '='){
                    text +=symbol;
                    return Token::REL_OP; 
                }
                else
                {
                    in.unget();
                    return Token::REL_OP;
                }
            case '<': 
                text += symbol;
                symbol = in.get(); 
                if(symbol == '=')
                {
                    text +=symbol;
                    return Token::REL_OP; 
                }
                else
                {
                    in.unget();
                    return Token::REL_OP;
                }
            case '=': 
                text += symbol;
                symbol = in.get(); 
                if(symbol == '=')
                {
                    text +=symbol;
                    return Token::REL_OP; 
                }
                else
                    return Token::ERROR;
            case ':': 
                text += symbol;
                symbol = in.get();
                if( symbol == '=')
                {
                    text += symbol;
                    return Token::ASIG;
                }
                else if( symbol == ':')
                {
                    text += symbol;
                    return Token::DDPERIOD;
                }
                else
                    return Token::ERROR;
            case '"':   
                symbol = in.get();
                while(symbol != '"' && symbol != '\n' && symbol != EOF)
                {
                    text += symbol;
                    symbol = in.get();
                }
                if(symbol == '"')
                    return Token::STRING_LITERAL;
                else
                    return Token::ERROR;
            case EOF:
                return Token::Eof;
            default:
                if (isalpha(symbol) || symbol == '_')
                {
                    int op = 66;
                    while((isalpha(symbol) || isdigit(symbol) ||symbol == '_') && symbol != ' ')
                    {
                        text += symbol;
                        symbol = in.get();
                        for (int i = 0; i < 18; i++)
                        {
                            if(text == keyword[i] && (symbol == ' ' || symbol == '('))
                            {
                                op = i;
                                in.unget();
                                switch (op)
                                {
                                case 0: return Token::FALSE_LITERAL;
                                case 1: return Token::TRUE_LITERAL;
                                case 2: return Token::WHILE;
                                case 3: return Token::IF;
                                case 4: return Token::ELSE;
                                case 5: return Token::RETURN;
                                case 6: return Token::INICIO;
                                case 7: return Token::IF_THEN;
                                case 8: return Token::DO;
                                case 9: return Token::END;
                                case 10: return Token::STATIC_TKN;
                                case 11: return Token::INT_TYPE;
                                case 12: return Token::ANYTYPE_TYPE;
                                case 13: return Token::BOOLEAN_TYPE;
                                case 14: return Token::VOID_TYPE;
                                case 15: return Token::REAL_TYPE;
                                case 16: return Token::STRING_TYPE;
                                case 17: return Token::DATE_TYPE;
                                }
                            }
                        }
                    }
                    in.unget();
                    return Token::ID;
                }
                else if(isdigit(symbol))
                {
                    text += symbol;
                    symbol = in.get();
                    while(isdigit(symbol) || symbol == '.')
                    {
                        if(symbol == '.')
                        {
                            text += symbol;
                            symbol = in.get();
                            if(isdigit(symbol))
                            {
                                text += symbol;
                                symbol = in.get();
                                while(isdigit(symbol))
                                {
                                    text += symbol;
                                    symbol = in.get();
                                }
                                in.unget();
                                return Token::REAL_LITERAL;
                            }
                            else
                                return Token::ERROR;                            
                        }
                        text += symbol;
                        symbol = in.get();
                    }
                    in.unget();
                    return Token::INT_LITERAL;
                }
        }
    }
}

/*
else if (isdigit(symbol))
                {
                    text += symbol;
                    symbol = in.get();
                    if(isdigit(symbol)){
                        text += symbol;
                        symbol = in.get();
                        if (symbol == '/')
                        {
                            text += symbol;
                            symbol = in.get();
                            if (isdigit(symbol))
                            {
                                text+=symbol;
                                symbol=in.get();
                                if (isdigit(symbol))
                                {
                                    text+=symbol;
                                    symbol=in.get();
                                    if(symbol == '/')
                                    {
                                        text+=symbol;
                                        symbol=in.get();
                                        if (isdigit(symbol))
                                        {
                                            text += symbol;
                                            symbol = in.get();
                                                if (isdigit(symbol))
                                                {
                                                    text += symbol;
                                                    symbol = in.get();
                                                    if (isdigit(symbol))
                                                    {
                                                        text += symbol;
                                                        symbol = in.get();
                                                        if (isdigit(symbol))
                                                        {
                                                            text += symbol;
                                                            return Token::DATE_LITERAL;
                                                        }
                                                    }
                                                }
                                        }
                                    }
                                }
                            }
                        }
                        else if (isdigit(symbol) || symbol == '.')
                        {
                            if(symbol == '.')
                            {
                                text+=symbol;
                                symbol= in.get();
                                if(isdigit(symbol))
                                {
                                    text += symbol;
                                    while (isdigit(symbol))
                                    {
                                        text += symbol;
                                        symbol = in.get();
                                    }
                                    in.unget();
                                    return Token::REAL_LITERAL;
                                }
                            }
                        }
                    }
                }
*/
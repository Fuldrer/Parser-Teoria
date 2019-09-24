#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include "doctest.h"
#include "lexer.h"

const char *test1 = "+ - * / || && < <= > >= == := . :: ++ ";

TEST_CASE("Lexer Operators")
{
    std::istringstream ins;
    ins.str(test1);
    Lexer l(ins);
    try
    {
        CHECK(l.getNextToken() == Token::ADD_OP);
        REQUIRE(l.getText() == "+");
        CHECK(l.getNextToken() == Token::ADD_OP);
        REQUIRE(l.getText() == "-");
        CHECK(l.getNextToken() == Token::MULT_OP);
        REQUIRE(l.getText() == "*");
        CHECK(l.getNextToken() == Token::MULT_OP);
        REQUIRE(l.getText() == "/");
        CHECK(l.getNextToken() == Token::LOG_OP);
        REQUIRE(l.getText() == "||");
        CHECK(l.getNextToken() == Token::LOG_OP);
        REQUIRE(l.getText() == "&&");
        CHECK(l.getNextToken() == Token::REL_OP);
        REQUIRE(l.getText() == "<");
        CHECK(l.getNextToken() == Token::REL_OP);
        REQUIRE(l.getText() == "<=");
        CHECK(l.getNextToken() == Token::REL_OP);
        REQUIRE(l.getText() == ">");
        CHECK(l.getNextToken() == Token::REL_OP);
        REQUIRE(l.getText() == ">=");
        CHECK(l.getNextToken() == Token::REL_OP);
        REQUIRE(l.getText() == "==");
        CHECK(l.getNextToken() == Token::ASIG);
        REQUIRE(l.getText() == ":=");
        CHECK(l.getNextToken() == Token::PERIOD);
        REQUIRE(l.getText() == ".");
        CHECK(l.getNextToken() == Token::DDPERIOD);
        REQUIRE(l.getText() == "::");
        CHECK(l.getNextToken() == Token::INCR);
        REQUIRE(l.getText() == "++");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

const char *test2 = "false true while //asdasdasd \n if else EXIT BEGIN THEN DO END static int anytype boolean void real String date _aaaddd ";

TEST_CASE("Lexer Types")
{
    std::istringstream ins;
    ins.str(test2);
    Lexer l(ins);
    try
    {
        CHECK(l.getNextToken() == Token::FALSE_LITERAL);
        REQUIRE(l.getText() == "false");
        CHECK(l.getNextToken() == Token::TRUE_LITERAL);
        REQUIRE(l.getText() == "true");
        CHECK(l.getNextToken() == Token::WHILE);
        REQUIRE(l.getText() == "while");
        CHECK(l.getNextToken() == Token::IF);
        REQUIRE(l.getText() == "if");
        CHECK(l.getNextToken() == Token::ELSE);
        REQUIRE(l.getText() == "else");
        CHECK(l.getNextToken() == Token::RETURN);
        REQUIRE(l.getText() == "EXIT");
        CHECK(l.getNextToken() == Token::INICIO);
        REQUIRE(l.getText() == "BEGIN");
        CHECK(l.getNextToken() == Token::IF_THEN);
        REQUIRE(l.getText() == "THEN");
        CHECK(l.getNextToken() == Token::DO);
        REQUIRE(l.getText() == "DO");
        CHECK(l.getNextToken() == Token::END);
        REQUIRE(l.getText() == "END");
        CHECK(l.getNextToken() == Token::STATIC_TKN);
        REQUIRE(l.getText() == "static");
        CHECK(l.getNextToken() == Token::INT_TYPE);
        REQUIRE(l.getText() == "int");
        CHECK(l.getNextToken() == Token::ANYTYPE_TYPE);
        REQUIRE(l.getText() == "anytype");
        CHECK(l.getNextToken() == Token::BOOLEAN_TYPE);
        REQUIRE(l.getText() == "boolean");
        CHECK(l.getNextToken() == Token::VOID_TYPE);
        REQUIRE(l.getText() == "void");
        CHECK(l.getNextToken() == Token::REAL_TYPE);
        REQUIRE(l.getText() == "real");
        CHECK(l.getNextToken() == Token::STRING_TYPE);
        REQUIRE(l.getText() == "String");
        CHECK(l.getNextToken() == Token::DATE_TYPE);
        REQUIRE(l.getText() == "date");
        CHECK(l.getNextToken() == Token::ID);
        REQUIRE(l.getText() == "_aaaddd");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

const char *test3 = "12 2.3 2.33 22.33 345 \"stringconstant\"";

TEST_CASE("Lexer Int Types")
{
    std::istringstream ins;
    ins.str(test3);
    Lexer l(ins);
    try
    {
        CHECK(l.getNextToken() == Token::INT_LITERAL);
        REQUIRE(l.getText() == "12");
        CHECK(l.getNextToken() == Token::REAL_LITERAL);
        REQUIRE(l.getText() == "2.3");
        CHECK(l.getNextToken() == Token::REAL_LITERAL);
        REQUIRE(l.getText() == "2.33");
        CHECK(l.getNextToken() == Token::REAL_LITERAL);
        REQUIRE(l.getText() == "22.33");
        CHECK(l.getNextToken() == Token::INT_LITERAL);
        REQUIRE(l.getText() == "345");
        CHECK(l.getNextToken() == Token::STRING_LITERAL);
        REQUIRE(l.getText() == "stringconstant");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

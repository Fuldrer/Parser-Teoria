#include <iostream>
#include <fstream>
#include "parser.h"
#include <exception>

int main(int argc, char *argv[])
{
  std::ifstream file(argv[1]);
  if(file.is_open())
  {
    Lexer l(file);
    /*Token token;
    token = l.getNextToken();
    while(token != Token::Eof)
    {
      std::cout << "Token " << l.getText() << " " << std::to_string(int(token)) << std::endl;
      token = l.getNextToken();
    }*/
    Parser parser(l);
    bool success = false;
    try
    {
      parser.prog();
      success = true;
    }
    catch(std::string msg)
    {
      std::cout << "Error: " << msg << '\n';
      success = false;
    }
    if(success)
    {
      std::cout << "Parsed without errors " << std::endl;
    }
  }
  return 0;
}
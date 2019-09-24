#include "parser.h"

void Parser::prog(){
    std::cout << "Prog() -> ";
    token = lexer.getNextToken();
    optional_func_dec();
}

void Parser::optional_func_dec(){
    std::cout << "Optional_func_decl() -> " ;
    func_head();
    body();
    if(token == Token::STATIC_TKN)
        optional_func_dec();
    else
    { /* Do nothing here */ }
}

void Parser::func_head(){
    std::cout << "Func_head() -> " ;
    func_name();
    param_list();
}

void Parser::func_name(){
    std::cout << "Func_name() -> " ;
    func_type();
    if(token == Token::ID){
        std::cout << "\n | ID" ;
        token = lexer.getNextToken();
    }
    else
        throw "Se esperaba token ID pero se encontro: " + lexer.getText();
    
}

void Parser::func_type(){
    std::cout << "Func_type() -> " ;
    func_modifiers();
    decl_type();
}

void Parser::func_modifiers(){
    std::cout << "func_modifiers() -> " ;
    if(token == Token::STATIC_TKN)
    {
        func_mods();
    }
    else
    { /* Nothing to do here */ }
}

void Parser::func_mods(){
    std::cout << "Func_mods() -> " ;
    if(token == Token::STATIC_TKN){
        token = lexer.getNextToken();
        std::cout<<"\n | STATIC_TKN"<<std::endl;
    }
}

void Parser::decl_type(){
    std::cout << "Decl_type() -> " ;
    if(token == Token::INT_TYPE){
        token = lexer.getNextToken();
        std::cout<<"| INT_TYPE"<<std::endl;
    }
    else if(token == Token::ANYTYPE_TYPE){
        token = lexer.getNextToken();
        std::cout<<"| ANYTYPE_TYPE"<<std::endl;
    }
    else if(token == Token::BOOLEAN_TYPE){
        token = lexer.getNextToken();
        std::cout<<"| BOOLEAN_TYPE"<<std::endl;
    }
    else if(token ==  Token::VOID_TYPE){
        token = lexer.getNextToken();
        std::cout<<"| VOID_TYPE"<<std::endl;
    }
    else if(token == Token::REAL_TYPE){
        token = lexer.getNextToken();
        std::cout<<"| REAL_TYPE"<<std::endl;
    }
    else if(token == Token::STRING_TYPE){
        token = lexer.getNextToken();
        std::cout<<"| STRING_TYPE"<<std::endl;
    }
    else if(token == Token::DATE_TYPE){
        token = lexer.getNextToken();
        std::cout<<"| DATE_TYPE"<<std::endl;
    }
}

void Parser::param_list_opt(){
    std::cout << "Param_list_opt() -> " ;
    param_list();
}

void Parser::param_list(){
    std::cout << "Param_list() -> " ;
    decl_param();
    param_list_p();
}

void Parser::param_list_p(){
    std::cout << "Param_list_p() -> " ;
    if(token == Token::COMA)
    {
        token = lexer.getNextToken();
        decl_param();
        param_list_p();
    }
}

void Parser::decl_param(){
    std::cout << "Decl_param() -> " ;
    decl_type();
    if(token == Token::ID){
        std::cout << "\n | ID" ;
        token = lexer.getNextToken();
    }
    else
        throw "Se esperaba token ID pero se encontro: " + lexer.getText();
}

void Parser::body(){
    std::cout << "Body() -> " ;
    if (token == Token::BRACES_OP)
    {
        token = lexer.getNextToken();
        stmt_list();
        if (token == Token::BRACES_END)
            token = lexer.getNextToken();
        else
            throw "Se esperaba token BRACES_END pero se encontro " + lexer.getText();
    }
    else
        throw "Se esperaba token BRACES_OP pero se encontro " + lexer.getText();
}

void Parser::stmt_list(){
    std::cout << "stmt_list() -> " ;
    stmt();
}

void Parser::stmts(){
    std::cout << "stmts() -> " ;
    stmt();
    stmt_p();
}

void Parser::stmt_p(){
    std::cout << "stmt_p() -> " ;
    if(token == Token::BRACES_OP || token == Token::WHILE || token == Token::IF
        || token == Token::ID || token == Token::RETURN)
    {
        stmt();
        stmt_p();
    }
}

void Parser::stmt(){
    std::cout << "stmt() -> " ;
    if (token == Token::BRACES_OP)
    {
        compound_stmt();
    }
    else if(token == Token::WHILE){
        while_stmt();
    }
    else if(token == Token::IF){
        if_stmt();
    }
    else if(token == Token::RETURN){
        return_stmt();
    }
    
}

void Parser::compound_stmt(){
    if (token == Token::BRACES_OP)
    {
        token = lexer.getNextToken();
        stmt_list();
        if (token == Token::BRACES_END)
            token = lexer.getNextToken();
        else
            throw "Se esperaba token BRACES_END pero se encontro " + lexer.getText();
        
    }
    else
        throw "Se esperaba token BRACES_OP pero se encontro " + lexer.getText();
    
}

void Parser::while_stmt(){
    std::cout << "while stmt() ->" ;
    while_test();
    stmt();
}

void Parser::while_test(){
    std::cout << "while_test() -> " ;
    if(token == Token::WHILE)
    {
        token = lexer.getNextToken();
        if(token == Token::PAR_OP){
            token = lexer.getNextToken();
            bool_expr();
            if(token == Token::PAR_END){
                token = lexer.getNextToken();
            }
            else
                throw "Se esperaba token PAR_END pero se encontro " + lexer.getText();
        }
        else
            throw "Se esperaba token PAR_OP pero se encontro " + lexer.getText();
    }
    
}

void Parser::if_stmt(){
    std::cout << "if_stmt() -> " ;
    if_conds();
    else_stmt();
}

void Parser::if_conds(){
    std::cout << "if_conds() -> " ;
    if_cond();
}

void Parser::if_cond(){
    if(token == Token::IF)
    {
        token = lexer.getNextToken();
        if(token == Token::PAR_OP){
            token = lexer.getNextToken();
            bool_expr();
            if(token == Token::PAR_END){
                token = lexer.getNextToken();
            }
            else
                throw "Se esperaba token PAR_END pero se encontro " + lexer.getText();
        }
        else
            throw "Se esperaba token PAR_OP pero se encontro " + lexer.getText();
    }
    else
        throw "Se esperaba token IF pero se encontro " + lexer.getText();
}

void Parser::else_stmt(){
    std::cout << "else_stmt() -> " ;
    else_r();
    stmt();
}

void Parser::else_r(){
    std::cout << "else_r() -> " ;
    if_conds();
    if(token == Token::ELSE)
        token = lexer.getNextToken();
}

void Parser::expr_stmt(){
    std::cout << "expr_stmt() -> " ;
}

void Parser::asg_stmt(){
    if(token == Token::ID){
        token = lexer.getNextToken();
        if (token == Token::ASIG){
            token = lexer.getNextToken();
            bool_expr();
        }
    }
    else{
        field();
        token = lexer.getNextToken();
        if(token == Token::ASIG){
            token = lexer.getNextToken();
            bool_expr();
        }
    }
}

void Parser::return_stmt(){
    if(token == Token::RETURN){
        token = lexer.getNextToken();
        if(token == Token::SEMICOLON){

        }
        else{
            bool_expr();
            token = lexer.getNextToken();
            if(token == Token::SEMICOLON){
                 token = lexer.getNextToken();
            }   
        }
    }
}

void Parser::bool_expr(){

}

void Parser::expr(){

}

void Parser::simple_expr(){

}

void Parser::term(){

}

void Parser::factor(){
    if(token == Token::PAR_OP){
        token = lexer.getNextToken();
        bool_expr();
        if (token == Token::PAR_END)
        {
             token = lexer.getNextToken();
        }
        else
            throw "Se esperaba token ) pero se encontro " + lexer.getText();
    }
    else{
        constant();
    }
}

void Parser::constant(){
    std::cout << "constant() -> " ;
    if(token == Token::INT_LITERAL)
    {
        std::cout << "\n | INT_LITERAL" << std::endl;
        token = lexer.getNextToken();
    }
    else if(token == Token::REAL_LITERAL)
    {
        std::cout << "\n | REAL_LITERAL" << std::endl;
        token = lexer.getNextToken();
    
    }
    else if(token == Token::DATE_LITERAL)
    {
        std::cout << "\n | DATE_LITERAL" << std::endl;
        token = lexer.getNextToken();
    }
    else if(token == Token::STRING_LITERAL)
    {
        std::cout << "\n | STRING_LITERAL" << std::endl;
        token = lexer.getNextToken();
    }
    else if(token == Token::TRUE_LITERAL)
    {
        std::cout << "\n | TRUE_LITERAL" << std::endl;
        token = lexer.getNextToken();
    }
    else if(token == Token::FALSE_LITERAL)
    {
        std::cout << "\n | FALSE_LITERAL" << std::endl;
        token = lexer.getNextToken();
    }
    else if(token == Token::ID)
        qualifier();
}

void Parser::field(){

}

void Parser::qualifier(){
    std::cout << "\n | Qualifier" << std::endl;
    if(token == Token::ID){
        token = lexer.getNextToken();
        if(token == Token::PERIOD){
            token = lexer.getNextToken();
        }
        else if (token == Token::DDPERIOD){
            token = lexer.getNextToken();
        }
    }
    else{
        eval();
        if(token == Token::PERIOD){
            token = lexer.getNextToken();
        }
    }
}

void Parser::eval(){
    std::cout << "eval() -> ";
    eval_name();
    par_list();
    if(token == Token::PAR_END)
        token = lexer.getNextToken();
    else
        throw "Se esperaba token ) pero se encontro " + lexer.getText();
}

void Parser::eval_name(){
    std::cout << "eval_name() -> " ;
    if(token == Token::ID)
    {
        token = lexer.getNextToken();
        if(token ==  Token::PAR_OP)
            token = lexer.getNextToken();
        else
            throw "Se esperaba token ( pero se encontro " + lexer.getText();
    }
    else
        throw "Se esperaba token ID pero se encontro " + lexer.getText();
}

void Parser::par_list(){

}

void Parser::prm_list(){

}

void Parser::function(){
    if(token == Token::ID){
        token = lexer.getNextToken();
        if(token == Token::PAR_OP){
            token == lexer.getNextToken();
            par_list();
             if(token == Token::PAR_END){
                token = lexer.getNextToken();
            }
            else
                throw "Se esperaba token PAR_END pero se encontro " + lexer.getText();
        }
        else
            throw "Se esperaba token PAR_OP pero se encontro " + lexer.getText();
    }
}

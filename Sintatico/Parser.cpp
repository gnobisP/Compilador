#include "Parser.h"

#include <iostream>
#include <stdexcept>

// Construtor/destrutor adaptados
Parser::Parser(const vector<pair<int,string>> &tokens)
    : tokens(tokens), pos(0), currentLexeme("") {}

Parser::~Parser() {}

// Inicia o parser
void Parser::app() {
    program();
}

// Retorna a tag do token atual
int Parser::tag() {
    if (pos >= (int)tokens.size()) return -1; 
   
    return tokens[pos].first;
}

// Retorna o lexema do token atual
string Parser::lexeme() {
    if (pos >= (int)tokens.size()) return "<EOF>";
    return tokens[pos].second;
}

// Avança um token da lista
void Parser::advance() {
    if (pos < (int)tokens.size()) {
        currentLexeme = tokens[pos].second;
        pos++;
    } else {
        currentLexeme = "<EOF>";
    }
}

void Parser::eat(int expectedTag) {
    
    if (tag() == expectedTag) {
        advance();
    } else {
        error(string("Missing token: expected ") +
              to_string(expectedTag) +
              " but got '" + lexeme() + "'");
    }
}

[[noreturn]] void Parser::error(const string &msg) {
    throw runtime_error(string("Syntax error: ") + msg +
                        " -- at token: '" + lexeme() + "'");
}

/* =========================
   Implementação das produções
   ========================= */

// program ::= app [decl-list] { stmt-list }
void Parser::program() {
    cout<<"program ::= app [decl-list] { stmt-list }"<<endl;
    if (tag() == -1) error("EOF at program app");

    if (tag() == Tag::APP) {
        eat(Tag::APP);
        eat(Tag::ID);
        
        int auxiliar = tag();
        

        if (auxiliar == Tag::TYPE_INT || auxiliar == Tag::TYPE_FLOAT || auxiliar == Tag::TYPE_STRING){
            decl_list();
        }

        stmt_list();
    } else {
        error("Missing 'app' keyword at beginning of program");
    }
}

// decl-list ::= decl { decl }
void Parser::decl_list() {
    cout<<"decl-list ::= decl { decl }"<<endl;
    if (tag() == -1) error("EOF in decl_list");

    if (tag() == Tag::TYPE_INT || tag() == Tag::TYPE_FLOAT || tag() == Tag::TYPE_STRING) {
        decl();
        while (tag() == Tag::TYPE_INT || tag() == Tag::TYPE_FLOAT || tag() == Tag::TYPE_STRING) {
            decl();
        }
    } else {
        error("Wrong declaration in decl_list");
    }
}

// decl ::= type ident-list ";"
void Parser::decl() {
    cout<<"decl ::= type ident-list ';'"<<endl;
    if (tag() == -1) error("EOF in decl");

    if (tag() == Tag::TYPE_INT || tag() == Tag::TYPE_FLOAT || tag() == Tag::TYPE_STRING) {
        type();
        ident_list();
        eat(Tag::PT_SEMI);
    } else {
        error("Missing type declaration or semicolon in decl");
    }
}

// ident-list ::= identifier { "," identifier }
void Parser::ident_list() {
    cout<<"ident-list ::= identifier { ',' identifier }"<<endl;
    if (tag() == -1) error("EOF in ident_list");
    if (tag() == Tag::ID) {
        identifier();
        while (tag() == Tag::PT_COMMA) {
            eat(Tag::PT_COMMA);
            identifier();
        }
    } else {
        error("Missing identifier in ident_list");
    }
}

// type ::= int | real | string | char
void Parser::type() {
    cout<<"type ::= int | real | string | char"<<endl;
    if (tag() == -1) error("EOF in type");

    switch (tag()) {
        case Tag::TYPE_INT: eat(Tag::TYPE_INT); break;
        case Tag::TYPE_FLOAT: eat(Tag::TYPE_FLOAT); break;
        case Tag::TYPE_STRING: eat(Tag::TYPE_STRING); break;
        case Tag::CONST_CHAR: eat(Tag::CONST_CHAR); break;
        default:
            error("Missing type declaration (int, real, string or char)");
    }
}

// 
void Parser::stmt_list() {
    cout<<"stmt-list ::= { stmt }"<<endl;
    if (tag() == -1) error("EOF in stmt_list");
    int aux;


    while (tag() == Tag::ID || tag() == Tag::RES_IF || tag() == Tag::RES_DO ||
           tag() == Tag::RES_WHILE || tag() == Tag::RES_SCAN || tag() == Tag::RES_PRINT ||
           tag() == Tag::PT_OBRA) 
    {   
        aux = tag();
        
        stmt();
    }
}

// stmt ::= assign-stmt | if-stmt | while-stmt | dowhile-stmt | read-stmt | write-stmt | block
void Parser::stmt() {
    cout<<"stmt ::= assign-stmt | if-stmt | while-stmt | dowhile-stmt | read-stmt | write-stmt | block"<<endl;
    if (tag() == -1) error("EOF in stmt");

    if (tag() == Tag::ID) {
        assign_stmt();
        eat(Tag::PT_SEMI);
    } 
    else if (tag() == Tag::RES_IF) {
        if_stmt();
    }
    else if (tag() == Tag::RES_DO) {
        eat(Tag::RES_DO);
        eat(Tag::PT_OBRA);
        stmt_list();
        eat(Tag::PT_CBRA);
        eat(Tag::RES_WHILE);
        eat(Tag::PT_OPAR);
        expression();
        eat(Tag::PT_CPAR);
        eat(Tag::PT_SEMI);
    }
    else if (tag() == Tag::RES_WHILE) {
        eat(Tag::RES_WHILE);
        eat(Tag::PT_OPAR);
        expression();
        eat(Tag::PT_CPAR);
        eat(Tag::RES_DO);
        eat(Tag::PT_OBRA);
        stmt_list();
        eat(Tag::PT_CBRA);
    }
    else if (tag() == Tag::RES_SCAN) {
        read_stmt();
        eat(Tag::PT_SEMI);
    }
    else if (tag() == Tag::RES_PRINT) {
        write_stmt();
        eat(Tag::PT_SEMI);
    }
    else if (tag() == Tag::PT_OBRA) {
        eat(Tag::PT_OBRA);
        stmt_list();
        eat(Tag::PT_CBRA);
    }
    else {
        error("Invalid app of statement");
    }
}

// assign-stmt ::= identifier "=" simple_expr
void Parser::assign_stmt() {
    if (tag() == -1) error("EOF in assign_stmt");

    if (tag() == Tag::ID) {
        identifier();
        eat(Tag::OP_ASG);
        simple_expression();
    } else {
        error("Missing identifier in assign_stmt");
    }
}

// if-stmt ::= if "(" expression ")" "{" stmt-list "}" [ else "{" stmt-list "}" ]
void Parser::if_stmt() {
    if (tag() == -1) error("EOF in if_stmt");

    eat(Tag::RES_IF);
    eat(Tag::PT_OPAR);
    expression();
    eat(Tag::PT_CPAR);
    eat(Tag::PT_OBRA);
    stmt_list();
    eat(Tag::PT_CBRA);

    if (tag() == Tag::RES_ELSE) {
        eat(Tag::RES_ELSE);
        eat(Tag::PT_OBRA);
        stmt_list();
        eat(Tag::PT_CBRA);
    }
}

// read-stmt ::= scan "(" identifier ")"
void Parser::read_stmt() {
    if (tag() == -1) error("EOF in read_stmt");

    eat(Tag::RES_SCAN);
    eat(Tag::PT_OPAR);
    identifier();
    eat(Tag::PT_CPAR);
}

// write-stmt ::= print "(" simple-expr ")"
void Parser::write_stmt() {
    cout<<"write-stmt ::= print '(' simple-expr ')' "<<endl;
    
    if (tag() == -1) error("EOF in write_stmt");

    eat(Tag::RES_PRINT);
    eat(Tag::PT_OPAR);
    simple_expression();
    eat(Tag::PT_CPAR);
}

// expression ::= simple_expr [ relop simple_expr ]
void Parser::expression() {
    if (tag() == -1) error("EOF in expression");

    simple_expression();

    if (tag() == Tag::CP_DF || tag() == Tag::CP_EQ || tag() == Tag::CP_GE ||
        tag() == Tag::CP_GT || tag() == Tag::CP_LE || tag() == Tag::CP_LT)
    {
        relop();
        simple_expression();
    }
}

// simple_expr ::= term { addop term }
// simple_expr ::= term | simple_expr addop term #TODO CORRETO
void Parser::simple_expression() {
    cout<<"simple_expr ::= term { addop term }"<<endl;
    if (tag() == -1) error("EOF in simple_expression");

    term();

    while (tag() == Tag::OP_ADD || tag() == Tag::OP_SUB || tag() == Tag::RL_OR) {
        addop();
        term();
    }
}

// term ::= factor-a { mulop factor-a }
void Parser::term() {
    cout<<"term ::= factor-a { mulop factor-a }"<<endl;
    if (tag() == -1) error("EOF in term");

    factor_a();

    while (tag() == Tag::OP_MUL || tag() == Tag::OP_DIV || tag() == Tag::RL_AND) {
        mulop();
        factor_a();
    }
}

// factor-a ::= factor | "!" factor | "-" factor
void Parser::factor_a() { 
    cout<<"factor-a ::= factor | '!'' factor | "-" factor"<<endl;
    if (tag() == -1) error("EOF in factor_a");

    if (tag() == Tag::RL_NOT) {
        eat(Tag::RL_NOT);
        factor();
    } 
    else if (tag() == Tag::OP_SUB) {
        eat(Tag::OP_SUB);
        factor();
    }
    else {
        factor();
    }
}

// factor ::= identifier | constant | "(" expression ")"
void Parser::factor() {
    int aux = tag();
    if (tag() == -1) error("EOF in factor");

    if (tag() == Tag::ID) {
        identifier();
    }
    else if (tag() == Tag::LIT_INT || tag() == Tag::LIT_FLOAT || tag() == Tag::LIT_STRING || tag() == Tag::CONST_CHAR || tag() == Tag::PT_OBRA) {
        constant();
    }
    else if (tag() == Tag::PT_OPAR) {
        eat(Tag::PT_OPAR);
        expression();
        eat(Tag::PT_CPAR);
    }
    else {
        error("Invalid factor");
    }
}

// relop
void Parser::relop() {
    if (tag() == -1) error("EOF in relop");

    switch (tag()) {
        case Tag::CP_EQ: eat(Tag::CP_EQ); break;
        case Tag::CP_GT: eat(Tag::CP_GT); break;
        case Tag::CP_GE: eat(Tag::CP_GE); break;
        case Tag::CP_LT: eat(Tag::CP_LT); break;
        case Tag::CP_LE: eat(Tag::CP_LE); break;
        case Tag::CP_DF: eat(Tag::CP_DF); break;
        default: error("Missing relational operator");
    }
}

// addop ::= "+" | "-" | "||"
void Parser::addop() {
    cout<<"addop ::= '+' | '-' | '||'";
    if (tag() == -1) error("EOF in addop");

    switch (tag()) {
        case Tag::OP_ADD: eat(Tag::OP_ADD); break;
        case Tag::OP_SUB: eat(Tag::OP_SUB); break;
        case Tag::RL_OR:  eat(Tag::RL_OR);  break;
        default: error("Missing additive operator");
    }
}

// mulop ::= "*" | "/" | "&&"
void Parser::mulop() {
    cout<<"mulop ::= '*' | '/' | '&&'"<<endl;
    if (tag() == -1) error("EOF in mulop");

    switch (tag()) {
        case Tag::OP_MUL: eat(Tag::OP_MUL); break;
        case Tag::OP_DIV: eat(Tag::OP_DIV); break;
        case Tag::RL_AND: eat(Tag::RL_AND); break;
        default: error("Missing multiplicative operator");
    }
}

// constant ::= integer_const | float_const | char_const | literal
void Parser::constant() {
    if (tag() == -1) error("EOF in constant");

    if (tag() == Tag::LIT_INT) integer_const();
    else if (tag() == Tag::LIT_FLOAT) float_const();
    else if (tag() == Tag::CONST_CHAR) eat(Tag::CONST_CHAR);
    else if (tag() == Tag::LIT_STRING) literal();
    else error("Missing constant");
}

void Parser::integer_const() {
    if (tag() == -1) error("EOF in integer_const");
    eat(Tag::LIT_INT);
}

void Parser::float_const() {
    if (tag() == -1) error("EOF in float_const");
    eat(Tag::LIT_FLOAT);
}

// literal ::= \"{\" LIT_STRING \"}\"
void Parser::literal() {
    if (tag() == -1) error("EOF in literal");

    if (tag() == Tag::LIT_STRING) {
        eat(Tag::LIT_STRING);
    } else {
        error("Missing string literal inside braces");
    }
}

// identifier ::= ID
void Parser::identifier() {
    if (tag() == -1) error("EOF in identifier");
    if (tag() == Tag::ID) {
        eat(Tag::ID);
    } else {
        error("Missing identifier");
    }
}

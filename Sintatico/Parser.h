#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <stdexcept>

#include "../Lexico/tokens/Token.h"
#include "../Lexico/Lexer.h"
#include "../Lexico/tokens/Tag.h"

using namespace std;

class Parser {
public:
    Parser(const vector<pair<int,string>> &tokens);
    ~Parser();

    void app();

private:
    vector<pair<int,string>> tokens;
    int pos;                   // índice do token atual
    int tag();                 // retorna tag do token atual
    string lexeme();           // retorna lexema do token atual
    string currentLexeme;

    void advance();
    void eat(int expectedTag);
    [[noreturn]] void error(const string &msg);

    // Suas regras da gramática:
    void program();
    void decl_list();
    void decl();
    void ident_list();
    void type();

    void stmt_list();
    void stmt();
    void assign_stmt();
    void if_stmt();
    void read_stmt();
    void write_stmt();

    void expression();
    void simple_expression();
    void term();
    void factor_a();
    void factor();

    void relop();
    void addop();
    void mulop();

    void constant();
    void integer_const();
    void float_const();
    void literal();
    void identifier();
};

#endif
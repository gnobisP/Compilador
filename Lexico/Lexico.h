#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cctype>
#include <string>
#include "tokens/Token.h"
#include "tokens/Word.h"
#include "tokens/LiteralInteger.h"
#include "tokens/LiteralFloat.h"
#include "tokens/LiteralString.h"

using namespace std;

class Lexer {
public:
    static int line; // contador de linhas
    static unordered_map<string, Word> words; // tabela de símbolos
    static unordered_map<Token, int> errors;  // tabela de erros

private:
    char apt = ' ';      // caractere atual
    ifstream file;      // arquivo fonte

    void reserve(Word w);
    void readch();
    bool readch(char c);

public:
    Lexer(const string& fileName);
    Token scan();
};

#endif

#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cctype>
#include <string>
#include <stdexcept>
#include <exception>
#include "tokens/Token.h"
#include "tokens/Word.h"
#include "tokens/LiteralInteger.h"
#include "tokens/LiteralFloat.h"
#include "tokens/LiteralString.h"
#include "tokens/ConstChar.h"

using namespace std;

class Lexer {
public:
    static int line; // contador de linhas
    static unordered_map<string, const Word*> words;  // tabela de símbolos
    static unordered_map<Token*, int> errors;         // tabela de erros

private:
    char ch = ' ';      // caractere atual
    ifstream file;      // arquivo fonte

    // ---------- Funções internas ----------
    void reserve(const Word* w);
    void readch();
    bool readch(char c);
    void addErro(int line);

    // ---------- Funções auxiliares de análise ----------
    const Token* scanIdentifier();               // lê identificadores e palavras reservadas
    const Token* scanNumber();                   // lê números inteiros ou float
    const Token* scanString();                   // lê strings entre aspas duplas
    const Token* scanChar();                     // lê constantes de caractere
    bool skipComments();                         // ignora comentários (// ou /* ... */)
    const Token* scanOperatorOrPunctuation();    // trata operadores e pontuação

public:
    // ---------- Construtor e função principal ----------
    Lexer(const string& fileName);
    const Token* scan(); // retorna o próximo token
};

#endif

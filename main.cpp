#include <iostream>
#include <stdexcept>
#include <string>
#include "Lexico/Lexer.h"
#include "Lexico/tokens/Token.h"
#include "Lexico/tokens/Word.h"
#include "Lexico/tokens/LiteralInteger.h"
#include "Lexico/tokens/LiteralFloat.h"
#include "Lexico/tokens/LiteralString.h"
#include "Lexico/tokens/Tag.h"

using namespace std;

// Função auxiliar para converter tag em string legível
std::string tagToString(int tag) {
    switch (tag) {
        // Identificador
        case Tag::ID: return "IDENTIFICADOR";

        // Literais
        case Tag::LIT_INT: return "LIT_INT";
        case Tag::LIT_FLOAT: return "LIT_FLOAT";
        case Tag::LIT_STRING: return "LIT_STRING";

        // Palavras reservadas
        case Tag::RES_START: return "START";
        case Tag::RES_EXIT: return "EXIT";
        case Tag::RES_END: return "END";
        case Tag::RES_IF: return "IF";
        case Tag::RES_THEN: return "THEN";
        case Tag::RES_ELSE: return "ELSE";
        case Tag::RES_DO: return "DO";
        case Tag::RES_WHILE: return "WHILE";
        case Tag::RES_SCAN: return "SCAN";
        case Tag::RES_PRINT: return "PRINT";

        // Pontuação
        case Tag::PT_SEMI: return "SEMICOLON";
        case Tag::PT_COMMA: return "COMMA";
        case Tag::PT_DOT: return "DOT";
        case Tag::PT_OPAR: return "OPEN_PAREN";
        case Tag::PT_CPAR: return "CLOSE_PAREN";
        case Tag::PT_OBRA: return "OPEN_BRACE";
        case Tag::PT_CBRA: return "CLOSE_BRACE";

        // Operadores relacionais
        case Tag::RL_AND: return "AND";
        case Tag::RL_OR: return "OR";
        case Tag::RL_NOT: return "NOT";

        // Operadores aritméticos
        case Tag::OP_ADD: return "ADD";
        case Tag::OP_SUB: return "SUB";
        case Tag::OP_MUL: return "MUL";
        case Tag::OP_DIV: return "DIV";
        case Tag::OP_ASG: return "ASSIGN";

        // Operadores de comparação
        case Tag::CP_GT: return "GREATER";
        case Tag::CP_GE: return "GREATER_EQUAL";
        case Tag::CP_LT: return "LESS";
        case Tag::CP_LE: return "LESS_EQUAL";
        case Tag::CP_DF: return "DIFFERENT";
        case Tag::CP_EQ: return "EQUAL";

        // Tipos
        case Tag::TYPE_INT: return "INT";
        case Tag::TYPE_FLOAT: return "FLOAT";
        case Tag::TYPE_STRING: return "STRING";

        // Fim de arquivo
        case Tag::END_OF_FILE: return "EOF";

        default: return "UNKNOWN";
    }
}

int main(int argc, char* argv[]) {
    // Caminho do arquivo (pode ser alterado conforme necessidade)
    const string var = "Teste/teste1.txt";
    const string filePath = var;

    try {
        Lexer lexer(filePath);

        cout << "-------------------------------------------------------------------------\n";
        cout << "TOKENS\n";
        cout << "------\n";

        int i = 0;
        int j = -1;

        while (true) {
            j++;
            const Token* scanned = lexer.scan();

            if (scanned->tag == static_cast<int>(Tag::END_OF_FILE))
                break;

            // Determina lexema/valor do token
            string lexeme;
            if (const Word* w = dynamic_cast<const Word*>(scanned)) {
                lexeme = w->getLexeme();
            } else if (const LiteralInteger* li = dynamic_cast<const LiteralInteger*>(scanned)) {
                lexeme = li->toString();
            } else if (const LiteralFloat* lf = dynamic_cast<const LiteralFloat*>(scanned)) {
                lexeme = lf->toString();
            } else if (const LiteralString* ls = dynamic_cast<const LiteralString*>(scanned)) {
                lexeme = ls->toString();
            } else {
                lexeme = "?";
            }

            // Imprime no formato <numero, TAG, lexema>
            cout << "<" << scanned->tag << "  " << tagToString(scanned->tag) << "  " << lexeme << ">"<<endl;

        }

        cout << "\n-------------------------------------------------------------------------\n";
        cout << "SYMBOL TABLE\n";
        cout << "------------\n";

        for (const auto& entry : Lexer::words) {
            const string& lexeme = entry.first;
            const Word* word = entry.second;
            cout << "[Token: " << word->toString() << ", Lexeme: " << lexeme << "]" << endl;
        }

        cout << "-------------------------------------------------------------------------\n";

        if (!Lexer::errors.empty()) {
            cout << "ERROR REPORT\n";
            cout << "------------\n";
            for (const auto& entry : Lexer::errors) {
                const Token* token = entry.first;
                int line = entry.second;
                cout << "ERROR: Pattern '" << (char)token->tag
                     << "' not recognized in line " << line << endl;
            }
        } else {
            cout << "Compilation successful!" << endl;
        }

    } catch (const runtime_error& e) {
        cerr << "Erro: " << e.what() << endl;
    } catch (...) {
        cerr << "Erro desconhecido!" << endl;
    }

    return 0;
}

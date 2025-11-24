#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Lexico/Lexer.h"
#include "Lexico/tokens/Token.h"
#include "Lexico/tokens/Word.h"
#include "Lexico/tokens/LiteralInteger.h"
#include "Lexico/tokens/LiteralFloat.h"
#include "Lexico/tokens/LiteralString.h"
#include "Lexico/tokens/ConstChar.h"
#include "Lexico/tokens/Tag.h"

#include "Sintatico/Parser.h"   
 
using namespace std;

int main(int argc, char *argv[])
{
    const string filePath = "testeSintatico/teste5_4.txt";
    vector<pair<int, string>> tokens;

    try
    {
        Lexer lexer(filePath);

        cout << "-------------------------------------------------------------------------\n";
        cout << "TOKENS (Analise Lexica)\n";
        cout << "--------------------------------------------------------------------------\n";

        // Executa primeiro apenas o léxico para exibir os tokens
        while (true)
        {
            const Token *scanned = lexer.scan();

            if (scanned->tag == Tag::END_OF_FILE)
                break;

            string lexeme;

            if (const Word *w = dynamic_cast<const Word *>(scanned))
                lexeme = w->getLexeme();
            else if (const LiteralInteger *li = dynamic_cast<const LiteralInteger *>(scanned))
                lexeme = li->toString();
            else if (const LiteralFloat *lf = dynamic_cast<const LiteralFloat *>(scanned))
                lexeme = lf->toString();
            else if (const LiteralString *ls = dynamic_cast<const LiteralString *>(scanned))
                lexeme = ls->toString();
            else if (const ConstChar *lc = dynamic_cast<const ConstChar *>(scanned))
                lexeme = lc->toString();

            cout << "<" << scanned->tag << ", " << tagToString(scanned->tag)
                 << ", " << lexeme << ">\n";
            tokens.push_back({scanned->tag, lexeme});
        }

        cout << "\n-------------------------------------------------------------------------\n";
        cout << "Tabela de simbolos\n";
        cout << "---------------------------------------------------------------------------\n";

        for (const auto &entry : Lexer::words)
        {
            const string &lexeme = entry.first;
            const Word *word = entry.second;
            cout << "[Token: " << word->toString() << " , Lexeme: " << lexeme << "]\n";
        }

        cout << "\n-------------------------------------------------------------------------\n";
        cout << "Iniciando ANALISE SINTATICA...\n";
        cout << "-------------------------------------------------------------------------\n";

        Parser parser(tokens);

        parser.app();  // chama a regra inicial

        cout << "\n==> Sintaxe correta! Nenhum erro encontrado.\n";
    }
    catch (runtime_error &e)
    {
        cerr << "\n Erro sintático: " << e.what() << "\n";
    }
    catch (...)
    {
        cout << "\n Erro desconhecido\n";

        cout << "Reporte de erros\n";
        cout << "------------\n";
        for (const auto &entry : Lexer::errors)
        {
            const Token *token = entry.first;
            int line = entry.second;
            cout << "ERROR: Caracter '" << (char)token->tag
                 << "' nao reconhecido na linha " << line << endl;
        }
    }

    return 0;
}

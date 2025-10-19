#include <iostream>
#include <stdexcept>
#include <string>
#include "Lexico/Lexer.h"
#include "Lexico/tokens/Token.h"
#include "Lexico/tokens/Word.h"
#include "Lexico/tokens/LiteralInteger.h"
#include "Lexico/tokens/LiteralFloat.h"
#include "Lexico/tokens/LiteralString.h"
#include "Lexico/tokens/ConstChar.h"
#include "Lexico/tokens/Tag.h"

using namespace std;



int main(int argc, char *argv[])
{
    // Caminho do arquivo (pode ser alterado conforme necessidade)
    const string var = "Teste_lexico/teste6_0.txt";
    const string filePath = var;

    try
    {
        Lexer lexer(filePath);

        cout << "-------------------------------------------------------------------------\n";
        cout << "TOKENS\n";
        cout << "--------------------------------------------------------------------------\n";

        while (true)
        {
            const Token *scanned = lexer.scan();

            if (scanned->tag == static_cast<int>(Tag::END_OF_FILE))
                break;

            // Determina lexema/valor do token
            string lexeme;
            if (const Word *w = dynamic_cast<const Word *>(scanned))
            {
                lexeme = w->getLexeme();
            }
            else if (const LiteralInteger *li = dynamic_cast<const LiteralInteger *>(scanned))
            {
                lexeme = li->toString();
            }
            else if (const LiteralFloat *lf = dynamic_cast<const LiteralFloat *>(scanned))
            {
                lexeme = lf->toString();
            }
            else if (const LiteralString *ls = dynamic_cast<const LiteralString *>(scanned))
            {
                lexeme = ls->toString();
            }
            else if (const ConstChar *lc = dynamic_cast<const ConstChar *>(scanned))
            {
                lexeme = lc->toString();
                
            }

            // Imprime no formato <numero, TAG, lexema>
            cout << "<" << scanned->tag << "  " << tagToString(scanned->tag) << "  " << lexeme << ">" << endl;
        }

        cout << "\n-------------------------------------------------------------------------\n";
        cout << "Tabela de simbolos\n";
        cout << "---------------------------------------------------------------------------\n";

        for (const auto &entry : Lexer::words)
        {
            const string &lexeme = entry.first;
            const Word *word = entry.second;
            cout << "[Token: " << word->toString() << ", Lexeme: " << lexeme << "]" << endl;
        }

        cout << "-------------------------------------------------------------------------\n";
        cout << "Compilacao realizada com sucesso!" << endl;
    }
    catch (...)
    {
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

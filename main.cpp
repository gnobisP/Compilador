#include <iostream>
#include <stdexcept>
#include "Lexico/Lexer.h"

using namespace std;

int main() {
    try {
        Lexer lexer("Teste/teste2.txt");  // pode lançar exceção
       
    }
    catch (const std::runtime_error& e) {  // captura exceções de runtime
        cerr << "Erro: " << e.what() << endl;  // imprime a mensagem da exceção
    }
    catch (...) {  // captura qualquer outra exceção genérica
        cerr << "Erro desconhecido!" << endl;
    }

    return 0;
}

#include "Tag.h"

string tagToString(int tag)
{
    switch (tag)
    {
    // Identificador
    case Tag::ID:
        return "IDENTIFICADOR";

    // Operadores de comparação
    case Tag::CP_GT:
        return "GREATER";
    case Tag::CP_GE:
        return "GREATER_EQUAL";
    case Tag::CP_LT:
        return "LESS";
    case Tag::CP_LE:
        return "LESS_EQUAL";
    case Tag::CP_DF:
        return "DIFFERENT";
    case Tag::CP_EQ:
        return "EQUAL";

    // Literais
    case Tag::LIT_INT:
        return "LIT_INT";
    case Tag::LIT_FLOAT:
        return "LIT_FLOAT";
    case Tag::LIT_STRING:
        return "LIT_STRING";
    case Tag::CONST_CHAR:
        return "CONST_CHAR";



    // Pontuação
    case Tag::PT_SEMI:
        return "SEMICOLON";
    case Tag::PT_COMMA:
        return "COMMA";
    case Tag::PT_DOT:
        return "DOT";
    case Tag::PT_OPAR:
        return "OPEN_PAREN";
    case Tag::PT_CPAR:
        return "CLOSE_PAREN";
    case Tag::PT_OBRA:
        return "OPEN_BRACE";
    case Tag::PT_CBRA:
        return "CLOSE_BRACE";

            // Palavras reservadas
    case Tag::RES_START:
        return "START";
    case Tag::RES_EXIT:
        return "EXIT";
    case Tag::RES_END:
        return "END";
    case Tag::RES_IF:
        return "IF";
    case Tag::RES_THEN:
        return "THEN";
    case Tag::RES_ELSE:
        return "ELSE";
    case Tag::RES_DO:
        return "DO";
    case Tag::RES_WHILE:
        return "WHILE";
    case Tag::RES_SCAN:
        return "SCAN";
    case Tag::RES_PRINT:
        return "PRINT";

    // Operadores aritméticos
    case Tag::OP_ADD:
        return "ADD";
    case Tag::OP_SUB:
        return "SUB";
    case Tag::OP_MUL:
        return "MUL";
    case Tag::OP_DIV:
        return "DIV";
    case Tag::OP_ASG:
        return "ASSIGN";

    // Operadores relacionais
    case Tag::RL_AND:
        return "AND";
    case Tag::RL_OR:
        return "OR";
    case Tag::RL_NOT:
        return "NOT";

    // Tipos
    case Tag::TYPE_INT:
        return "INT";
    case Tag::TYPE_FLOAT:
        return "FLOAT";
    case Tag::TYPE_STRING:
        return "STRING";

    // Fim de arquivo
    case Tag::END_OF_FILE:
        return "EOF";

    default:
        return "UNKNOWN";
    }
}
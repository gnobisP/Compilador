#ifndef TAG_H
#define TAG_H

class Tag {
public:
    // Palavras reservadas
    static const int RES_START;
    static const int RES_EXIT;
    static const int RES_END;
    static const int RES_IF;
    static const int RES_THEN;
    static const int RES_ELSE;
    static const int RES_DO;
    static const int RES_WHILE;
    static const int RES_SCAN;
    static const int RES_PRINT;

    // Pontuação
    static const int PT_SEMI;
    static const int PT_COMMA;
    static const int PT_DOT;
    static const int PT_OPAR;
    static const int PT_CPAR;
    static const int PT_OBRA;
    static const int PT_CBRA;

    // Operadores relacionais
    static const int RL_AND;
    static const int RL_OR;
    static const int RL_NOT;

    // Operadores aritméticos
    static const int OP_ADD;
    static const int OP_SUB;
    static const int OP_MUL;
    static const int OP_DIV;
    static const int OP_ASG;

    // Operadores de comparação
    static const int CP_GT;
    static const int CP_GE;
    static const int CP_LT;
    static const int CP_LE;
    static const int CP_DF;
    static const int CP_EQ;

    // Tipos
    static const int TYPE_INT;
    static const int TYPE_FLOAT;
    static const int TYPE_STRING;

    // Literais
    static const int LIT_INT;
    static const int LIT_FLOAT;
    static const int LIT_STRING;

    // Identificador
    static const int ID;

    // Fim de arquivo
    static const int END_OF_FILE;
};

#endif
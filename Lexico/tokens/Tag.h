#ifndef TAG_H
#define TAG_H

// Enumeração para todos os tags de token
enum Tag {
    // Identificador
    ID=256,

    // Literais
    LIT_INT,
    LIT_FLOAT,
    LIT_STRING,

    // Palavras reservadas
    RES_START,
    RES_EXIT,
    RES_END,
    RES_IF,
    RES_THEN,
    RES_ELSE,
    RES_DO,
    RES_WHILE,
    RES_SCAN,
    RES_PRINT,

    // Pontuação
    PT_SEMI,
    PT_COMMA,
    PT_DOT,
    PT_OPAR,
    PT_CPAR,
    PT_OBRA,
    PT_CBRA,

    // Operadores relacionais
    RL_AND,
    RL_OR,
    RL_NOT,

    // Operadores aritméticos
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_ASG,

    // Operadores de comparação
    CP_GT,
    CP_GE,
    CP_LT,
    CP_LE,
    CP_DF,
    CP_EQ,

    // Tipos
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,

    // Fim de arquivo
    END_OF_FILE
};

#endif

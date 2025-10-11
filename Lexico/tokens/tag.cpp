#ifndef TAG_H
#define TAG_H

class Tag {
public:
    // Palavras reservadas
    static const int RES_START = 256;
    static const int RES_EXIT  = 257;
    static const int RES_END   = 258;
    static const int RES_IF    = 259;
    static const int RES_THEN  = 260;
    static const int RES_ELSE  = 261;
    static const int RES_DO    = 262;
    static const int RES_WHILE = 263;
    static const int RES_SCAN  = 264;
    static const int RES_PRINT = 265;

    // Pontuação
    static const int PT_SEMI  = 266;
    static const int PT_COMMA = 267;
    static const int PT_DOT   = 268;
    static const int PT_OPAR  = 269;
    static const int PT_CPAR  = 270;
    static const int PT_OBRA  = 271;
    static const int PT_CBRA  = 272;

    // Operadores relacionais
    static const int RL_AND = 273;
    static const int RL_OR  = 274;
    static const int RL_NOT = 275;

    // Operadores aritméticos
    static const int OP_ADD = 276;
    static const int OP_SUB = 277;
    static const int OP_MUL = 278;
    static const int OP_DIV = 279;
    static const int OP_ASG = 280;

    // Operadores de comparação
    static const int CP_GT = 281;
    static const int CP_GE = 282;
    static const int CP_LT = 283;
    static const int CP_LE = 284;
    static const int CP_DF = 285;
    static const int CP_EQ = 286;

    // Tipos
    static const int TYPE_INT    = 287;
    static const int TYPE_FLOAT  = 288;
    static const int TYPE_STRING = 289;

    // Literais
    static const int LIT_INT    = 290;
    static const int LIT_FLOAT  = 291;
    static const int LIT_STRING = 292;

    // Identificador
    static const int ID = 293;

    // Fim de arquivo
    static const int END_OF_FILE = 65535;
};

#endif
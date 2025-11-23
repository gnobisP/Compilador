#ifndef TAG_H
#define TAG_H

#include <string>
using namespace std;
// Enumeração para todos os tags de token
enum Tag {

    // Identificador
    ID = 256,          // 256 – identificadores (nomes de variáveis, funções, etc.)

    // Literais
    LIT_INT,           // 257 – literal inteiro (ex: 10)
    LIT_FLOAT,         // 258 – literal float (ex: 3.14)
    LIT_STRING,        // 259 – literal string (ex: "abc")

    // Palavras reservadas
    RES_EXIT,          // 260 – palavra reservada: exit
    RES_END,           // 261 – palavra reservada: end (não usado sempre, depende da linguagem)
    RES_IF,            // 262 – if
    RES_THEN,          // 263 – then (aparece em linguagens tipo Pascal, depende da sua gramática)
    RES_ELSE,          // 264 – else
    RES_DO,            // 265 – do
    RES_WHILE,         // 266 – while
    RES_SCAN,          // 267 – scan (leitura)
    RES_PRINT,         // 268 – print (escrita)

    // Pontuação
    PT_SEMI,           // 269 – ponto e vírgula ';'
    PT_COMMA,          // 270 – vírgula ','
    PT_DOT,            // 271 – ponto '.'
    PT_OPAR,           // 272 – parêntese abrindo '('
    PT_CPAR,           // 273 – parêntese fechando ')'
    PT_OBRA,           // 274 – chave abrindo '{'
    PT_CBRA,           // 275 – chave fechando '}'

    // Operadores lógicos
    RL_AND,            // 276 – operador lógico AND  (&&)
    RL_OR,             // 277 – operador lógico OR   (||)
    RL_NOT,            // 278 – operador lógico NOT  (!)

    // Operadores aritméticos
    OP_ADD,            // 279 – soma        '+'
    OP_SUB,            // 280 – subtração   '-'
    OP_MUL,            // 281 – multiplicação '*'
    OP_DIV,            // 282 – divisão     '/'
    OP_ASG,            // 283 – atribuição  '='

    // Operadores de comparação
    CP_GT,             // 284 – greater than        '>'
    CP_GE,             // 285 – greater or equal    '>='
    CP_LT,             // 286 – less than           '<'
    CP_LE,             // 287 – less or equal       '<='
    CP_DF,             // 288 – different           '!='
    CP_EQ,             // 289 – equal               '=='

    // Tipos
    TYPE_INT,          // 290 – tipo int
    TYPE_FLOAT,        // 291 – tipo float
    TYPE_STRING,       // 292 – tipo string
    CONST_CHAR,        // 293 – literal de caractere (ex: 'a')

    // Especiais
    APP,               // 294 – símbolo especial (depende da sua gramática)

    // Fim de arquivo
    END_OF_FILE        // 295 – marca fim dos tokens
};


// Declaração da função
string tagToString(int tag);

#endif

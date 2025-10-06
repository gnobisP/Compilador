#include <string>
#include <iostream>
using namespace std;
#include "token.h"
#include "tag.h"

class word : public Token {
private:
    string lexeme;

public:
    Word(string s, int tag) : Token(tag), lexeme(s) {}

    string getLexeme() const { 
        return lexeme; 
    }

    string toString() const override { 
        return "<" + lexeme + ", " + to_string(tag) + ">"; 
    }
    inline static const Word start{"start", Tag::RES_START};
    inline static const Word exit{"exit", Tag::RES_EXIT};
    inline static const Word end{"end", Tag::RES_END};
    inline static const Word _if{"if", Tag::RES_IF};
    inline static const Word then{"then", Tag::RES_THEN};
    inline static const Word _else{"else", Tag::RES_ELSE};
    inline static const Word _do{"do", Tag::RES_DO};
    inline static const Word _while{"while", Tag::RES_WHILE};
    inline static const Word scan{"scan", Tag::RES_SCAN};
    inline static const Word print{"print", Tag::RES_PRINT};
    inline static const Word semi{";", Tag::PT_SEMI};
    inline static const Word comma{",", Tag::PT_COMMA};
    inline static const Word dot{".", Tag::PT_DOT};
    inline static const Word opar{"(", Tag::PT_OPAR};
    inline static const Word cpar{")", Tag::PT_CPAR};
    inline static const Word obra{"{", Tag::PT_OBRA};
    inline static const Word cbra{"}", Tag::PT_CBRA};
    inline static const Word and_{"&&", Tag::RL_AND};
    inline static const Word or_{"||", Tag::RL_OR};
    inline static const Word not_{"!", Tag::RL_NOT};
    inline static const Word add{"+", Tag::OP_ADD};
    inline static const Word sub{"-", Tag::OP_SUB};
    inline static const Word mul{"*", Tag::OP_MUL};
    inline static const Word div{"/", Tag::OP_DIV};
    inline static const Word asg{"=", Tag::OP_ASG};
    inline static const Word gt{">", Tag::CP_GT};
    inline static const Word ge{">=", Tag::CP_GE};
    inline static const Word lt{"<", Tag::CP_LT};
    inline static const Word le{"<=", Tag::CP_LE};
    inline static const Word df{"<>", Tag::CP_DF};
    inline static const Word eq{"==", Tag::CP_EQ};
    inline static const Word type_int{"int", Tag::TYPE_INT};
    inline static const Word type_float{"float", Tag::TYPE_FLOAT};
    inline static const Word type_string{"string", Tag::TYPE_STRING};
};
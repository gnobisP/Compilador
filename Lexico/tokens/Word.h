#ifndef WORD_H
#define WORD_H

#include <string>
#include "Token.h"
#include "Tag.h"
using namespace std;

class Word : public Token {
private:
    string lexeme;

public:
    Word(string s, int tag);
    string getLexeme() const;
    string toString() const;

    static const Word start, exit, end, _if, then, _else, _do, _while,
                      scan, print, semi, comma, dot, opar, cpar,
                      obra, cbra, and_, or_, not_, add, sub, mul, div,
                      asg, gt,ge,lt,le,df,eq,
                      type_int, type_float, type_string;
};

#endif
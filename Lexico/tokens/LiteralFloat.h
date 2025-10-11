#ifndef LITERALFLOAT_H
#define LITERALFLOAT_H

#include "Token.h"
#include "Tag.h"
#include <string>
using namespace std;

class LiteralFloat : public Token {
private:
    float value;

public:
    explicit LiteralFloat(float v);
    float getValue() const;
    string toString() const;
};
//teste para commit

#endif
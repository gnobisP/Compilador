#ifndef LITERALINTEGER_H
#define LITERALINTEGER_H

#include "Token.h"
#include "Tag.h"
#include <string>
#include <string>
#include <sstream>

using namespace std;

class LiteralInteger : public Token {
private:
    int value;

public:
    explicit LiteralInteger(int v);
    int getValue() const;
    string toString() const;
};

#endif

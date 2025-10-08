#ifndef LITERALSTRING_H
#define LITERALSTRING_H

#include "Token.h"
#include "Tag.h"
#include <string>
using namespace std;

class LiteralString : public Token {
private:
    string value;

public:
    explicit LiteralString(const string& v);
    string getValue() const;
    string toString() const;
};

#endif

#ifndef LITERALCHAR_H
#define LITERALCHAR_H

#include "Token.h"
#include "Tag.h"
#include <string>
using namespace std;

class ConstChar : public Token {
private:
    char value;

public:
    explicit ConstChar(char v);
    char getValue() const;
    string toString() const;
};

#endif

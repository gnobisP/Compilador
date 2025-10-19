#include "ConstChar.h"

ConstChar::ConstChar(char v)
    : Token(Tag::CONST_CHAR), value(v) {}

char ConstChar::getValue() const {
    return value;
}

string ConstChar::toString() const {
    return string(1, value)  + ", ";
}

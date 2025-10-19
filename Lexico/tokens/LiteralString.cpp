#include "LiteralString.h"

LiteralString::LiteralString(const string& v)
    : Token(Tag::LIT_STRING), value(v) {}

string LiteralString::getValue() const {
    return value;
}

string LiteralString::toString() const {
    return  value + ", ";
}

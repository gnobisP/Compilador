#include "LiteralString.h"
#include <string>
using namespace std;

LiteralString::LiteralString(const string& v)
    : Token(Tag::LIT_STRING), value(v) {}

string LiteralString::getValue() const {
    return value;
}

string LiteralString::toString() const {
    return "<" + value + ", " + to_string(tag) + ">";
}

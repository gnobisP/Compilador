#include "LiteralInteger.h"
#include <string>
#include <sstream>
using namespace std;

LiteralInteger::LiteralInteger(int v)
    : Token(Tag::LIT_INT), value(v) {}

int LiteralInteger::getValue() const {
    return value;
}

string LiteralInteger::toString() const {
    return "<" + to_string(value) + ", " + to_string(tag) + ">";
}

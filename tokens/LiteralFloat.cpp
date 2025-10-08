#include "LiteralFloat.h"
#include <string>
#include <sstream>
using namespace std;

LiteralFloat::LiteralFloat(float v)
    : Token(Tag::LIT_FLOAT), value(v) {}

float LiteralFloat::getValue() const {
    return value;
}
string LiteralFloat::toString() const {
    return "<" + to_string(value) + ", " + to_string(tag) + ">";
}
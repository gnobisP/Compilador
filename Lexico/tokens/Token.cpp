#include "Token.h"

Token::Token(int t) : tag(t) {}

string Token::toString() const {
    return "<" + to_string(tag) + ">";
}

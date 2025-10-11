#include "Token.h"
#include <string>

Token::Token(int t) : tag(t) {}

std::string Token::toString() const {
    return "<" + std::to_string(tag) + ">";
}

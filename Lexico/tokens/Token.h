#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

class Token {
public:
    const int tag;
    Token(int t);
    string toString() const;
};
#endif
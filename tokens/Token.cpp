#include <string>
using namespace std;

class Token {
public:
    const int tag; 

    Token(int t) : tag(t) {}

    virtual ~Token() {}

    virtual string toString() const {
        return "<" + to_string(tag) + ">";
    }
};
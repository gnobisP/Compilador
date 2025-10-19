#include "Word.h"
#include <string>
using namespace std;

Word::Word(string s, int tag) : Token(tag), lexeme(s) {}

string Word::getLexeme() const {
    return lexeme;
}

string Word::toString() const {
    return "<" + lexeme + ", " + to_string(tag) + ">";
}


const Word Word::start("start", Tag::RES_START);
const Word Word::exit("exit", Tag::RES_EXIT);
const Word Word::end("end", Tag::RES_END);
const Word Word::_if("if", Tag::RES_IF);
const Word Word::then("then", Tag::RES_THEN);
const Word Word::_else("else", Tag::RES_ELSE);
const Word Word::_do("do", Tag::RES_DO);
const Word Word::_while("while", Tag::RES_WHILE);
const Word Word::scan("scan", Tag::RES_SCAN);
const Word Word::print("print", Tag::RES_PRINT);
const Word Word::semi(";", Tag::PT_SEMI);
const Word Word::comma(",", Tag::PT_COMMA);
const Word Word::dot(".", Tag::PT_DOT);
const Word Word::opar("(", Tag::PT_OPAR);
const Word Word::cpar(")", Tag::PT_CPAR);
const Word Word::obra("{", Tag::PT_OBRA);
const Word Word::cbra("}", Tag::PT_CBRA);
const Word Word::_and("&&", Tag::RL_AND);
const Word Word::_or("||", Tag::RL_OR);
const Word Word::_not("!", Tag::RL_NOT);
const Word Word::add("+", Tag::OP_ADD);
const Word Word::sub("-", Tag::OP_SUB);
const Word Word::mul("*", Tag::OP_MUL);
const Word Word::div("/", Tag::OP_DIV);
const Word Word::asg("=", Tag::OP_ASG);
const Word Word::gt(">", Tag::CP_GT);
const Word Word::ge(">=", Tag::CP_GE);
const Word Word::lt("<", Tag::CP_LT);
const Word Word::le("<=", Tag::CP_LE);
const Word Word::df("<>", Tag::CP_DF);
const Word Word::eq("==", Tag::CP_EQ);
const Word Word::eof("EOF", Tag::END_OF_FILE);
const Word Word::type_int("int", Tag::TYPE_INT);
const Word Word::type_float("float", Tag::TYPE_FLOAT);
const Word Word::type_string("string", Tag::TYPE_STRING);
const Word Word::const_char("char", Tag::CONST_CHAR);

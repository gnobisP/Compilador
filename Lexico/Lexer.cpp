#include "Lexer.h"



int Lexer::line = 1;
unordered_map<string, const Word*> Lexer::words;
unordered_map<Token*, int> Lexer::errors;

// insere uma palavra reservada na tabela
void Lexer::reserve(const Word* w) {
    words[w->getLexeme()] = w;
}

// construtor
Lexer::Lexer(const string& fileName) {
    file.open(fileName);
    if (!file.is_open()) {
        cerr << "File not found: " << fileName << endl;
        throw runtime_error("File not found");
    }

    reserve(&Word::start);
    reserve(&Word::exit);
    reserve(&Word::end);
    reserve(&Word::_if);
    reserve(&Word::then);
    reserve(&Word::_else);
    reserve(&Word::_do);
    reserve(&Word::_while);
    reserve(&Word::scan);
    reserve(&Word::print);
    reserve(&Word::semi);
    reserve(&Word::comma);
    reserve(&Word::dot);
    reserve(&Word::opar);
    reserve(&Word::cpar);
    reserve(&Word::obra);
    reserve(&Word::cbra);
    reserve(&Word::and_);
    reserve(&Word::or_);
    reserve(&Word::not_);
    reserve(&Word::add);
    reserve(&Word::sub);
    reserve(&Word::mul);
    reserve(&Word::div);
    reserve(&Word::asg);
    reserve(&Word::gt);
    reserve(&Word::ge);
    reserve(&Word::lt);
    reserve(&Word::le);
    reserve(&Word::df);
    reserve(&Word::eq);
    reserve(&Word::type_int);
    reserve(&Word::type_float);
    reserve(&Word::type_string);
}

// lê próximo caractere
void Lexer::readch() {
    ch = file.get();
    if (file.eof()) {
        ch = EOF;
    }
}


// lê e compara com c
bool Lexer::readch(char c) {
    readch();
    if (ch != c) return false;
    ch = ' ';
    return true;
}

// método principal scan()
const Token* Lexer::scan() {

    // ignora espaços e quebras de linha
    for (;; readch()) {
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\b')
            continue;
        else if (ch == '\n')
            line++;
        else
            break;
    }

    // identifica comentários
    int line_aux = 0;
    while (ch == '/') {
        readch();
        if (ch == '/') { // comentário de linha
            do {
                readch();
                if (ch == '\n') {
                    readch();
                    line++;
                    break;
                }
            } while (ch != EOF);
        } else if (ch == '*') { // comentário de bloco
            line_aux = line;
            do {
                readch();
                if (ch == '\n') line++;
                if (ch == '*') {
                    readch();
                    if (ch == '/') {
                        readch();
                        break;
                    }
                }
            } while (ch != EOF);
        } else {
            return &Word::div;
        }

        if (ch == EOF) {
            Token* t = new Token('*');
            errors[t] = line_aux;
            return t;
        }
        if (isspace(ch)) ch = '/';
    }

    // pontuação
    switch (ch) {
        case ';': readch(); return &Word::semi;
        case ',': readch(); return &Word::comma;
        case '.': readch(); return &Word::dot;
        case '(': readch(); return &Word::opar;
        case ')': readch(); return &Word::cpar;
        case '{': readch(); return &Word::obra;
        case '}': readch(); return &Word::cbra;
    }

    // operadores
    switch (ch) {
        case '&':
            if (readch('&')) return &Word::and_;
            else { Token* t = new Token('&'); errors[t] = line; return t; }
        case '|':
            if (readch('|')) return &Word::or_;
            else { Token* t = new Token('|'); errors[t] = line; return t; }
        case '!': readch(); return &Word::not_;
        case '+': readch(); return &Word::add;
        case '-': readch(); return &Word::sub;
        case '*': readch(); return &Word::mul;
        case '/': readch(); return &Word::div;
        case '=':
            if (readch('=')) return &Word::eq;
            else return &Word::asg;
        case '>':
            if (readch('=')) return &Word::ge;
            else return &Word::gt;
        case '<':
            readch();
            if (ch == '=') return &Word::le;
            else if (ch == '>') return &Word::df;
            else return &Word::lt;
    }

    // números
    if (isdigit(ch)) {
        int value = 0;
        do {
            value = 10 * value + (ch - '0');
            readch();
        } while (isdigit(ch));

        if (ch != '.') {
            Word* w = new Word(to_string(value), Tag::LIT_INT);
            words[to_string(value)] = w;
            return new LiteralInteger(value);
        } else {
            readch();
            float valuef = value;
            float decUnit = 10;
            while (isdigit(ch)) {
                valuef += (ch - '0') / decUnit;
                decUnit *= 10;
                readch();
            }
            Word* w = new Word(to_string(value), Tag::LIT_FLOAT);
            words[to_string(value)] = w;
            return new LiteralFloat(valuef);
        }
    }

    // strings literais
    if (ch == '"') {
        string s;
        s += ch;
        readch();
        while (ch != '"' && ch != EOF) {
            s += ch;
            readch();
        }
        s += ch;
        readch();
        //Word* w = new Word(s, Tag::LIT_FLOAT);
        return new LiteralString(s);
    }

    // identificadores e palavras reservadas
    if (isalpha(ch) || ch == '_') {
        string s;
        do {
            s += ch;
            readch();
        } while (isalnum(ch) || ch == '_');

        auto it = words.find(s);
        if (it != words.end()) return it->second;
        Word* w = new Word(s, Tag::ID);//Para identificadores devemos colocar a tag ID e o valor literal
        words[s] = w;
        return w;
    }

    // final de arquivo
    if(ch == EOF)
       return &Word::eof;

    // erro genérico
    Token* t = new Token(ch);
    if (ch != EOF) errors[t] = line;

    // lança uma exceção com uma mensagem explicando o erro
    if (ch != EOF) {
        throw std::runtime_error("Erro léxico na linha " + std::to_string(line) + 
                                ": caractere inválido '" + std::string(1, ch) + "'");
        printf("Erro léxico na linha ");
    }

    ch = ' ';
    return t;
}

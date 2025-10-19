#include "Lexer.h"

int Lexer::line = 1;
unordered_map<string, const Word *> Lexer::words;
unordered_map<Token *, int> Lexer::errors;


void Lexer::reserve(const Word *w)
{
    words[w->getLexeme()] = w;
}

Lexer::Lexer(const string &fileName)
{
    file.open(fileName);
    if (!file.is_open())
    {
        cerr << "Verifique o nome do arquivo: " << fileName << endl;
        throw runtime_error("File not found");
    }

    // Palavras reservadas
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
    reserve(&Word::const_char);
}


void Lexer::readch()
{
    ch = file.get();
    if (file.eof())
        ch = EOF;
}

bool Lexer::readch(char c)
{
    readch();
    if (ch != c)
        return false;
    ch = ' ';
    return true;
}

//Erro
void Lexer::addErro(int line)
{
    Token *t = new Token(ch);
    if (ch != EOF)
        errors[t] = line;
    throw new exception();
}


// ID ou palavra reservada
const Token *Lexer::scanIdentifier()
{
    string s;
    do
    {
        s += ch;
        readch();
    } while (isalnum(ch) || ch == '_');

    auto it = words.find(s);
    if (it != words.end())
        return it->second;

    Word *w = new Word(s, Tag::ID);
    words[s] = w;
    return w;
}

// nuemros float e int
const Token *Lexer::scanNumber()
{
    int value = 0;
    do
    {
        value = 10 * value + (ch - '0');
        readch();
    } while (isdigit(ch));

    if (ch != '.')
    {
        Word *w = new Word(to_string(value), Tag::LIT_INT);
        words[to_string(value)] = w;
        return new LiteralInteger(value);
    }

    readch();
    float valuef = value;
    float decUnit = 10;
    while (isdigit(ch))
    {
        valuef += (ch - '0') / decUnit;
        decUnit *= 10;
        readch();
    }

    Word *w = new Word(to_string(valuef), Tag::LIT_FLOAT);
    words[to_string(valuef)] = w;
    return new LiteralFloat(valuef);
}

// string
const Token *Lexer::scanString()
{
    string s;
    readch(); 

    while (ch != '"' && ch != EOF && ch != '\n')
    {
        s += ch;
        readch();
    }

    if (ch != '"')
        addErro(line);
    else
        readch(); 

    Word *w = new Word(s, Tag::LIT_STRING);
    words[s] = w;
    return new LiteralString(s);
}

// caracter
const Token *Lexer::scanChar()
{
    readch();
    char c = ch;
    readch();

    if (ch != '\'')
        addErro(line);

    readch(); 

    Word *w = new Word(to_string(c), Tag::LIT_INT);
    words[to_string(c)] = w;
    return new ConstChar(c);
}

// comaentarios
bool Lexer::skipComments()
{
    int line_aux = 0;

    if (ch == '/')
    {
        readch();
        if (ch == '/')
        { // comentário de linha
            do
            {
                readch();
                if (ch == '\n')
                {
                    line++;
                    readch();
                    break;
                }
            } while (ch != EOF);
            return true;
        }
        else if (ch == '*')
        { // comentário de bloco
            line_aux = line;
            do
            {
                readch();
                if (ch == '\n')
                    line++;
                if (ch == '*')
                {
                    readch();
                    if (ch == '/')
                    {
                        readch();
                        break;
                    }
                }
            } while (ch != EOF);

            if (ch == EOF)
            {
                Token *t = new Token('*');
                errors[t] = line_aux;
                return false;
            }
            return true;
        }
        else
        {
            return false; 
        }
    }
    return false;
}

// Operadores e pontuação
const Token *Lexer::scanOperatorOrPunctuation()
{
    switch (ch)
    {
    case ';':
        readch();
        return &Word::semi;
    case ',':
        readch();
        return &Word::comma;
    case '.':
        readch();
        return &Word::dot;
    case '(':
        readch();
        return &Word::opar;
    case ')':
        readch();
        return &Word::cpar;
    case '{':
        readch();
        return &Word::obra;
    case '}':
        readch();
        return &Word::cbra;
    case '&':
        if (readch('&'))
            return &Word::and_;
        else
        {
            Token *t = new Token('&');
            errors[t] = line;
            return t;
        }
    case '|':
        if (readch('|'))
            return &Word::or_;
        else
        {
            Token *t = new Token('|');
            errors[t] = line;
            return t;
        }
    case '!':
        readch();
        return &Word::not_;
    case '+':
        readch();
        return &Word::add;
    case '-':
        readch();
        return &Word::sub;
    case '*':
        readch();
        return &Word::mul;
    case '/':
        readch();
        return &Word::div;
    case '=':
        if (readch('='))
            return &Word::eq;
        else
            return &Word::asg;
    case '>':
        if (readch('='))
            return &Word::ge;
        else
            return &Word::gt;
    case '<':
        readch();
        if (ch == '=')
            return &Word::le;
        else if (ch == '>')
            return &Word::df;
        else
            return &Word::lt;
    }
    return nullptr;
}


const Token *Lexer::scan()
{
    // Ignora espaços e quebras de linha
    for (;; readch())
    {
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\b')
            continue;
        else if (ch == '\n')
            line++;
        else
            break;
    }

    // Comentarios
    if (ch == '/')
    {
        if (skipComments())
            return scan(); 
        else
            return &Word::div;
    }

    // Identificador
    if (isalpha(ch) || ch == '_')
        return scanIdentifier();

    // numeros
    if (isdigit(ch))
        return scanNumber();

    // String " "
    if (ch == '"')
        return scanString();

    // caractere ' ' 
    if (ch == '\'')
        return scanChar();

    // Operadores e pontuacao
    const Token *tok = scanOperatorOrPunctuation();
    if (tok != nullptr)
        return tok;

    // Fim de arquivo
    if (ch == EOF)
        return &Word::eof;

    // Erro léxico
    addErro(line);
    return nullptr;
}

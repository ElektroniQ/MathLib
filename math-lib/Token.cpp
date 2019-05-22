#include "Token.hpp"
#include <iostream>
/*Token::Token()
{}

Token::Token(const std::string& token) : token_(token)
{}

Token::Token(const char* token) :  token_(token)
{}

Token::token_t Token::getType()
{
    if(token_.empty())
    {
        return EMPTY;
    }
    if(token_=="(")
    {
        return BRACKET_OPEN;
    }
    if(token_==")")
    {
        return BRACKET_CLOSE;
    }
    if( (token_=="+")
      ||(token_=="-")
      ||(token_=="*")
      ||(token_=="/")
      ||(token_=="^"))
    {
        return OPERATOR;
    }

    if( (token_=="sin")
     || (token_=="cos")
     || (token_=="tan")
     || (token_=="tg")
     || (token_=="ctg")
     || (token_=="cot")
     || (token_=="arcsin")
     || (token_=="asin")
     || (token_=="arccos")
     || (token_=="acos")
     || (token_=="arctan")
     || (token_=="atan")
     || (token_=="arctg")
     || (token_=="arcctg")
     || (token_=="actg")
     || (token_=="arccot")
     || (token_=="acot")
     || (token_=="log")
     || (token_=="ln")
     || (token_=="sqrt")
     || (token_=="abs")
     || (token_=="exp")
     || (token_=="-sin")
     || (token_=="-cos")
     || (token_=="-tan")
     || (token_=="-tg")
     || (token_=="-ctg")
     || (token_=="-cot")
     || (token_=="-acos")
     || (token_=="-atan")
     || (token_=="-atg")
     || (token_=="-actg")
     || (token_=="-actan")
     || (token_=="-log")
     || (token_=="-ln")
     || (token_=="-sqrt")
     || (token_=="-abs")
     || (token_=="-exp"))
    {
        return FUNCTION;
    }

    int dot=0;
    size_t i=0;
    while(((token_[i]>=48) && (token_[i]<=57)) || (token_[i]=='.') || (token_[i]=='-'))
    {
        if((token_[i]=='.'))
        {
            dot++;
            if(dot>1)
            {
                return INVALID;
            }
        }
        //std::cout<<"kropka \n";
        if((token_[i]=='-') && i!=0)
        {
            return INVALID;
        }
        //std::cout<<"minus \n";
        i++;
    }
    //debug
    //std::cout << i <<" " << token_.size()-1;
    if(i==token_.size())
    {
        return NUMBER;
    }

    if( (token_[0]=='+')
      ||(token_[0]=='-')
      ||(token_[0]=='*')
      ||(token_[0]=='/')
      ||(token_[0]=='^')
      ||(token_[0]=='(')
      ||(token_[0]==')'))
    {
        return INVALID;
    }

    return VARIABLE;
}

std::string Token::toStr()
{
    return token_;
}

Token::token_t Token::set(const std::string& token)
{
    token_=token;
    return getType();
}

int Token::getPrecedence()
{
    if(getType()==token_t::OPERATOR)
    {
        if( (token_=="+")
          ||(token_=="-"))
        {
           return 1;
        }

        if( (token_=="*")
          ||(token_=="/"))
        {
           return 2;
        }

        if(token_=="^")
        {
           return 3;
        }

        return 0;
    }
    else
    {
        return -1;
    }
}

association_t Token::getAssociation()
{
    if(token_=="^")
        return association_t::RIGHT;
    else
        return association_t::LEFT;
}

bool  Token::operator==(const Token& token)
{
    if(token.token_==token_)
        return true;
    else
        return false;
}

bool  Token::operator==(const char* token)
{
    if(token==token_)
        return true;
    else
        return false;
}

Token&  Token::operator+=(Token token)
{
    token_+=token.token_;
    return *this;
}

Token&  Token::operator+=(char* token)
{
    token_+=token;
    return *this;
}

Token  Token::operator+(Token& token)
{
    Token a(token_);
    a.token_+=token.token_;
    return a;
}

Token  Token::operator+(char* token)
{
    Token a(token_);
    a.token_+=token;
    return a;
}

Token&  Token::operator=(const Token& token)
{
    token_=token.token_;
    return *this;
}

Token&  Token::operator=(char* token)
{
    token_=token;
    return *this;
}

char&  Token::operator[](size_t i)
{
    return token_[i];
}

std::ostream& operator<<(std::ostream& stream, Token& token)
{
    std::string type;
    token_t t=token.getType();
    switch(t)
    {
    case Token::NUMBER:
        type="NUMBER";
        break;
    case Token::OPERATOR:
        type="OPERATOR";
        break;
    case Token::FUNCTION:
        type="FUNCTION";
        break;
    case Token::VARIABLE:
        type="VARIABLE";
        break;
    case Token::BRACKET_OPEN:
        type="BRACKET_OPEN";
        break;
    case Token::BRACKET_CLOSE:
        type="BRACKET_CLOSE";
        break;
    case Token::EMPTY:
        type="EMPTY";
        break;
    case Token::INVALID:
        type="INVALID";
        break;
    }
    stream <<type<<": "<< token.token_;
    return stream;
}

std::istream& operator<<(std::istream& stream, Token& token)
{
    stream >> token.token_;
    return stream;
}
*/

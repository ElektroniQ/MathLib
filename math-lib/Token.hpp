#pragma once

#include <string>
#include "FunctionGroup.hpp"
#include <ostream>
#include <istream>
#include <iostream>

enum token_t
{
    NUMBER,
    OPERATOR,
    FUNCTION,
    VARIABLE,
    BRACKET_OPEN,
    BRACKET_CLOSE,
    FUNC_COMMA,
    EMPTY,
    INVALID
};

enum association_t
{
    LEFT = 0,
    RIGHT = 1
};

template<class T_string = std::string, typename T1 = double, typename T2 = double>
class basic_Token 
	: 
	public T_string
{
private:
    basic_FunctionSet<T1, T2>* functions = nullptr;
    basic_FunctionSet<T1, T2>* operators = nullptr;
    unsigned int last_pos_;
public:
    basic_Token();
    basic_Token(const T_string& str);
	basic_Token(const char* str);
    basic_Token(const basic_Token<T_string, T1, T2>& str);
 
    void SetFunctions(basic_FunctionSet<T1, T2>& functions);
    void SetOperators(basic_FunctionSet<T1, T2>& operators);
    token_t GetType();
    int GetPrecedence();
    size_t GetArgCount();
    association_t GetAssociation();
    T1 GetNumber();
#if T1!=T2
    T2 getNumber();
#endif
    T1 operator()(std::vector<T2>& arg_vec);
    basic_Token<T_string, T1, T2>& operator=(basic_Token<T_string, T1, T2> a);
    unsigned int GetLastPos();
    void SetLastPos(unsigned int pos);
};

template<typename T1 = double, typename T2 = double> using Token_t = basic_Token<std::string, T1, T2>;
typedef Token_t<> Token;

template<class T_string, typename T1, typename T2>
basic_Token<T_string, T1, T2>::basic_Token() 
	:
	T_string()
{}

template<class T_string, typename T1, typename T2>
basic_Token<T_string, T1, T2>::basic_Token(const T_string& str) 
	: 
	T_string(str)
{}

template<class T_string, typename T1, typename T2>
basic_Token<T_string, T1, T2>::basic_Token(const char* str)
	:
	T_string(str)
{}

template<class T_string, typename T1, typename T2>
basic_Token<T_string, T1, T2>::basic_Token(const basic_Token<T_string, T1, T2>& str) 
	: 
	T_string(str)
{
    this->functions=str.functions;
    this->operators=str.operators;
}

template<class T_string, typename T1, typename T2> 
void basic_Token<T_string, T1, T2>::SetFunctions(basic_FunctionSet<T1, T2>& functions)
{
    this->functions = &functions;
}

template<class T_string, typename T1, typename T2>
void basic_Token<T_string, T1, T2>::SetOperators(basic_FunctionSet<T1, T2>& operators)
{
    this->operators = &operators;
}

template<class T_string, typename T1, typename T2>
token_t basic_Token<T_string, T1, T2>::GetType()
{
    if(this->empty())
    {
        return token_t::EMPTY;
    }
    if(*this=="(" || *this=="[" || *this=="{")
    {
        return token_t::BRACKET_OPEN;
    }
    if(*this==")" || *this=="]" || *this=="}")
    {
        return token_t::BRACKET_CLOSE;
    }
    if(*this==",")
    {
        return token_t::FUNC_COMMA;
    }
    if((operators!=nullptr) && (operators->GetArgCount(*this))>0)
    {
        return token_t::OPERATOR;
    }

    if((functions!=nullptr) && (functions->GetArgCount(*this))>0)
    {
        return token_t::FUNCTION;
    }
    int dot=0;
    size_t i;
    for(i=0; i<this->size(); i++)
    {
        if(((this->at(i)>=48) && (this->at(i)<=57)) || (this->at(i)=='.') || (this->at(i)=='-'))
        {
            if((this->at(i)=='.'))
            {
                dot++;
                if(dot>1)
                {
                    return INVALID;
                }
            }
            if((this->at(i)=='-') && i!=0)
            {
                return INVALID;
            }
        }
        else
        {
            break;
        }
    }

    if(i==this->size())
    {
        return NUMBER;
    }

    if( (this->at(0)=='+')
      ||(this->at(0)=='*')
      ||(this->at(0)=='/')
      ||(this->at(0)=='^')
      ||(this->at(0)=='(')
      ||(this->at(0)==')'))
    {
        return INVALID;
    }

    return VARIABLE;
}

template<class T_string, typename T1, typename T2>
int basic_Token<T_string, T1, T2>::GetPrecedence()
{
	if ((operators != nullptr) && (operators->GetPrecedence(*this) > 0))
	{
		return operators->GetPrecedence(*this);
	}

	if ((functions != nullptr) && (functions->GetPrecedence(*this) > 0))
	{
		return functions->GetPrecedence(*this);
	}

    return 0;
}

template<class T_string, typename T1, typename T2>
size_t basic_Token<T_string, T1, T2>::GetArgCount()
{
	if ((operators != nullptr) && (operators->GetArgCount(*this) > 0))
	{
		return operators->GetArgCount(*this);
	}

	if ((functions != nullptr) && (functions->GetArgCount(*this) > 0))
	{
		return functions->GetArgCount(*this);
	}

    return 0;
}

template<class T_string, typename T1, typename T2>
association_t  basic_Token<T_string, T1, T2>::GetAssociation()
{
	if (operators != nullptr)
	{
		return (association_t)operators->getAssociation(*this);
	}

    throw std::invalid_argument("Token::getAssociation(): operators not set.");
}

template<class T_string, typename T1, typename T2>
T1 basic_Token<T_string, T1, T2>::GetNumber()
{
    return (T1)std::stod(*this);
}
#if T1!=T2
template<class T_string, typename T1, typename T2> 
T2 basic_Token<T_string, T1, T2>::getNumber()
{
    return (T2)std::stod(*this);
}
#endif

template<class T_string, typename T1, typename T2>
T1 basic_Token<T_string, T1, T2>::operator()(std::vector<T2>& arg_vec)
{
    int signum=1;
    if((this->size()>0) && (this->operator[](0)=='-'))
        signum=-1;

    if((operators!=nullptr) && (operators->GetArgCount(*this)>0))
    {
        return signum*operators->operator[](*this)(arg_vec);
    }

    if((functions!=nullptr) && (functions->GetArgCount(*this)>0))
    {
        return signum*functions->operator[](*this)(arg_vec);
    }

    throw std::invalid_argument("Token::operator(): functions/operators not set.");
}

template<class T_string, typename T1, typename T2>
basic_Token<T_string, T1, T2>& basic_Token<T_string, T1, T2>::operator=(basic_Token<T_string, T1, T2> a)
{
    T_string::operator=(a);
    this->operators=a.operators;
    this->functions=a.functions;
    return *this;
}

template<class T_string, typename T1, typename T2>
unsigned int basic_Token<T_string, T1, T2>::GetLastPos()
{
    return last_pos_;
}

template<class T_string, typename T1, typename T2> 
void basic_Token<T_string, T1, T2>::SetLastPos(unsigned int pos)
{
    last_pos_=pos;
}


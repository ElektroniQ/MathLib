#pragma once

#include "Token.hpp"
#include "FunctionGroup.hpp"
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>

template<class T, typename T1 = double, typename T2 = double>
class basic_TokenGroup : public std::vector<T>
{
private:
    basic_FunctionSet<T1, T2>* functions = nullptr;
    basic_FunctionSet<T1, T2>* operators = nullptr;
public:
    void SetFunctions(basic_FunctionSet<T1, T2>& functions);
    void SetOperators(basic_FunctionSet<T1, T2>& operators);
    template<typename T_arg> size_t Tokenize(T_arg& str);
    template<typename T_arg> void AddToken(T_arg& str);
    void AddToken(basic_Token<T>& str);
};

template<typename T1 = double, typename T2 = double> using TokenGroup_t = basic_TokenGroup<Token_t<T1, T2>, T1, T2>;
typedef TokenGroup_t<> TokenGroup;


template<class T, typename T1, typename T2>
void basic_TokenGroup<T, T1, T2>::SetFunctions(basic_FunctionSet<T1, T2>& functions)
{
    this->functions = &functions;
    for(auto& item : *this)
        item.SetFunctions(functions);
}

template<class T, typename T1, typename T2> 
void basic_TokenGroup<T, T1, T2>::SetOperators(basic_FunctionSet<T1, T2>& operators)
{
    this->operators = &operators;
    for(auto& item : *this)
        item.SetOperators(operators);
}

template<class T, typename T1, typename T2>
template<typename T_arg> size_t basic_TokenGroup<T, T1, T2>::Tokenize(T_arg& input)
{
    T str=input;
    for(auto iter=str.begin(); iter!=str.end(); ++iter)
        if(*iter==' ')
        {
            str.erase(iter);
			if (iter != str.begin())
			{
				--iter;
			}
        }

    T buffer;
    buffer.SetOperators(*operators);
    buffer.SetFunctions(*functions);
    T c;
    for(auto& b : str)
    {
        c="";
        c.SetOperators(*operators);
        c.SetFunctions(*functions);
        buffer.SetOperators(*operators);
        buffer.SetFunctions(*functions);
        c+=b;
        if((c.GetType()==token_t::FUNC_COMMA) || (c.GetType()==token_t::BRACKET_OPEN) || (c.GetType()==token_t::BRACKET_CLOSE) || (operators->GetArgCount(buffer)>0)||(operators->GetArgCount(c)>0))
        {
            if(!buffer.empty())
            {
                this->AddToken(buffer);
                buffer.clear();
            }
            this->AddToken(c);
        }
        else
        {
            buffer+=c;
        }
    }
    if(!buffer.empty())
    {
        this->AddToken(buffer);
    }

    token_t last_type=token_t::EMPTY;
    for(size_t i=0; i<this->size(); i++)
    {
        if(this->operator[](i)=="-")
        {
            if( (last_type==token_t::BRACKET_OPEN)
                    ||(last_type==token_t::EMPTY)
                    ||(last_type==token_t::OPERATOR))
            {
                this->operator[](i)+=this->operator[](i+1);
                this->erase(this->begin() + i+1);
            }
        }
        last_type=this->operator[](i).GetType();
    }
    return this->size();
}

template<class T, typename T1, typename T2> 
template<typename T_arg> void basic_TokenGroup<T, T1, T2>::AddToken(T_arg& str)
{
    T token;
    token=str;
    this->push_back(token);
    this->operator[](this->size()-1).SetFunctions(*functions);
    this->operator[](this->size()-1).SetOperators(*operators);
}

template<class T, typename T1, typename T2> 
void basic_TokenGroup<T, T1, T2>::AddToken(basic_Token<T>& str)
{
    T token;
    token=str;
    this->push_back(token);
    this->operator[](this->size()-1).SetFunctions(*functions);
    this->operator[](this->size()-1).SetOperators(*operators);
}

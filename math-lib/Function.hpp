#pragma once
#include <vector>
#include <string>
#include <cstdarg>
#include <iostream>
#include "Token.hpp"


template<typename T1, typename T2>
class basic_Function
{
public:
    typedef T1 (*vec_function_ptr)(std::vector<T2>&);
private:
    std::vector<std::string> names;
    vec_function_ptr functionPtr = nullptr;
    int argumentCount;
    int precedence = 0;
    int association = 0;

public:
    basic_Function();
    basic_Function(vec_function_ptr func);

    void SetArgCount(int arg_count);
    int GetArgCount();
    void SetPrecedence(int arg_count);
    int GetPrecedence();
    void SetAssociation(int a);
    int GetAssociation();
    void Bind(vec_function_ptr func);
    T1 operator()(T2 a, T2 b = 0);
    T1 operator()(std::vector<T2>& vec);
    void SetNames(const char* name1, ...);
    template<typename T_arg> bool operator==(const T_arg& a);
};

typedef basic_Function<double, double> Function;

template<typename T1, typename T2>
basic_Function<T1, T2>::basic_Function()
{}

template<typename T1, typename T2>
basic_Function<T1, T2>::basic_Function(vec_function_ptr func)
{
    functionPtr=func;
}

template<typename T1, typename T2>
void basic_Function<T1, T2>::SetArgCount(int arg_count)
{
    argumentCount=arg_count;
}

template<typename T1, typename T2>
int basic_Function<T1, T2>::GetArgCount()
{
    return argumentCount;
}

template<typename T1, typename T2>
void basic_Function<T1, T2>::SetPrecedence(int precedence)
{
    this->precedence=precedence;
}

template<typename T1, typename T2>
int basic_Function<T1, T2>::GetPrecedence()
{
    return precedence;
}

template<typename T1, typename T2>
void basic_Function<T1, T2>::SetAssociation(int a)
{
    association=a;
}

template<typename T1, typename T2>
int basic_Function<T1, T2>::GetAssociation()
{
    return association;
}

template<typename T1, typename T2>
void basic_Function<T1, T2>::Bind(vec_function_ptr func)
{
    functionPtr=func;
}

template<typename T1, typename T2>
T1 basic_Function<T1, T2>::operator()(T2 a, T2 b)
{
    std::vector<T2> args;
    args.push_back(a);
    args.push_back(b);
    if(functionPtr!=nullptr)
        return functionPtr(args);
    else
        throw std::invalid_argument("Function::operator(): function_ptr not set.");
}

template<typename T1, typename T2>
T1 basic_Function<T1, T2>::operator()(std::vector<T2>& vec)
{
   if(functionPtr!=nullptr)
        return functionPtr(vec);
    else
        throw std::invalid_argument("Function::operator(): function_ptr not set.");
}

template<typename T1, typename T2> 
void basic_Function<T1, T2>::SetNames(const char* name1, ...)
{
    names.clear();

    std::string str=name1;
    const char* tmp=name1;
    va_list vl;
    va_start(vl,name1);
    do
    {
        names.push_back(str);
        tmp=va_arg(vl,char*);
        if(tmp!=NULL) str=tmp;
    }
    while (tmp!=NULL);
    va_end(vl);
}

template<typename T1, typename T2>
template<typename T_arg>
bool basic_Function<T1, T2>::operator==(const T_arg& a)
{
    for(auto& item : names)
        if((item==a)||("-"+item)==a)
            return true;
    return false;
}


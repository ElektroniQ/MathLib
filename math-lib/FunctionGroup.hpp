#pragma once

#include <vector>
#include <stdexcept>
#include "Function.hpp"
#include "Token.hpp"


template<typename T1, typename T2>
class basic_FunctionSet : public std::vector<basic_Function<T1, T2>>
{
public:

    template<class T_arg> int GetArgCount(T_arg& name);
    template<class T_arg> int getAssociation(T_arg& name);
    template<class T_arg> int GetPrecedence(T_arg& name);

    template<class T_arg> basic_Function<T1, T2>& operator[](T_arg name);

    template<class T_arg> basic_Function<T1, T2>& at(T_arg name);
};

typedef basic_FunctionSet<double, double> FunctionSet;

template<typename T1, typename T2> template<class T_arg>
int basic_FunctionSet<T1, T2>::GetArgCount(T_arg& name)
{
    for(auto& item : *this)
    {
        if(item==name)
            return item.GetArgCount();
    }
    return 0;
}

template<typename T1, typename T2> template<class T_arg>
int basic_FunctionSet<T1, T2>::getAssociation(T_arg& name)
{
    for(auto& item : *this)
        if(item==name)
            return item.GetAssociation();
    return 0;
}

template<typename T1, typename T2> template<class T_arg>
int basic_FunctionSet<T1, T2>::GetPrecedence(T_arg& name)
{
    for(auto& item : *this)
        if(item==name)
            return item.GetPrecedence();
    return 0;
}

template<typename T1, typename T2> template<class T_arg>
basic_Function<T1, T2>& basic_FunctionSet<T1, T2>::at(T_arg name)
{
    for(auto& item : *this)
        if(item==name)
            return item;
    throw std::invalid_argument("FunctionGroup: function not found.");
}

template<typename T1, typename T2> template<class T_arg> 
basic_Function<T1, T2>& basic_FunctionSet<T1, T2>::operator[](T_arg name)
{
    return at(name);
}


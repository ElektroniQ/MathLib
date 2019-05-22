#pragma once

#include <map>
#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include "TokenGroup.hpp"
#include "FunctionGroup.hpp"
#include "Calc.hpp"

template<typename T, class T_string>
class basic_RPNcalc 
	: 
	public Calc<T, T_string>
{
public:
    basic_RPNcalc();
    virtual void ParseEquation(const T_string& equation);
    virtual T Compute() final;

private:
	void ValidateSyntax();
};

typedef basic_RPNcalc<double, std::string> RPNcalc;



template<typename T, class T_string> 
basic_RPNcalc<T, T_string>::basic_RPNcalc() 
	: 
	Calc<T, T_string>()
{

}

template<typename T, class T_string>
void basic_RPNcalc<T, T_string>::ParseEquation(const T_string& equation)
{
	T_string buffer;

    for(auto& ch : equation)
    {
        if(ch != ' ')
        {
            buffer += ch;
        }
        else
        {
            if(buffer.size()>0)
            {
                Calc<T, T_string>::equation.AddToken(buffer);
                buffer.clear();
            }
        }
    }
    if(buffer.size()>0)
    {
        Calc<T, T_string>::equation.AddToken(buffer);
        buffer.clear();
    }

	ValidateSyntax();
}

template<typename T, class T_string>
void basic_RPNcalc<T, T_string>::ValidateSyntax()
{
    for(auto& token : Calc<T,T_string>::equation)
    {
        if((token.GetType()!=token_t::FUNCTION) || (token.GetType()!=token_t::NUMBER) || (token.GetType()!=token_t::OPERATOR))
        {
            Calc<T, T_string>::syntaxErrors.push_back(SyntaxError(SyntaxError_t::INVALID_VALUE, token));
        }
    }
}

template<typename T, class T_string>
T basic_RPNcalc<T, T_string>::Compute()
{
    std::stack<T> stack;
    for(auto& currentToken : Calc<T, T_string>::equation)
    {
        if(currentToken.GetType()==token_t::NUMBER)
        {
            stack.push(currentToken.GetNumber());
        }
        else if(currentToken.GetType()==token_t::VARIABLE)
        {
            T_string var=currentToken;
            int signum=1;
            if(!var.empty() && var[0]=='-')
            {
                var.erase(var.begin());
                signum=-1;
            }
			if (Calc<T, T_string>::variables.IsVariable(var))
			{
				stack.push(signum * Calc<T, T_string>::variables.GetVariableValue(var));
			}
			else
			{
				auto error = SyntaxError(SyntaxError_t::VARIABLE_NOT_SET, currentToken);
				Calc<T, T_string>::syntaxErrors.push_back(error);
				return 0;
			}
        }
        else if((currentToken.GetType()==token_t::OPERATOR) || (currentToken.GetType()==token_t::FUNCTION))
        {
            std::vector<T> arguments;
            for(size_t i=0; i<currentToken.GetArgCount(); i++)
            {
                if(stack.size()>0)
                {
                    arguments.push_back(stack.top());
                    stack.pop();
                }
                else
                {
					auto error = SyntaxError(SyntaxError_t::TOO_FEW_ARGS, currentToken);
                    Calc<T, T_string>::syntaxErrors.push_back(error);
                    return 0;
                }
            }
            stack.push(currentToken(arguments));
        }
    }
    if(stack.size()!=1)
    {
        Calc<T, T_string>::syntaxErrors.push_back(SyntaxError_t::UNKNOWN);
        return 0;
    }
    return stack.top();
}


#pragma once

#include <map>
#include <string>
#include <vector>

#include "RPNcalc.hpp"
#include "TokenGroup.hpp"
#include "FunctionGroup.hpp"


template<typename T, class T_string>
class basic_InfixCalc 
	: 
	public basic_RPNcalc<T, T_string>
{
private:
    basic_TokenGroup<basic_Token<T_string, T, T>, T, T> infixTokenizedEquation;

public:
    basic_InfixCalc();
      
    virtual void ParseEquation(const T_string& input_str);
    T_string GetRPNEquation();
    virtual T_string GetEquation();

	~basic_InfixCalc();
};
typedef basic_InfixCalc<double, std::string> InfixCalc;

template<typename T, class T_string> 
basic_InfixCalc<T, T_string>::basic_InfixCalc() 
	: 
	basic_RPNcalc<T, T_string>()
{
    infixTokenizedEquation.SetFunctions(this->functions);
    infixTokenizedEquation.SetOperators(this->operators);
}

template<typename T, class T_string> 
void basic_InfixCalc<T, T_string>::ParseEquation(const T_string& input_str)
{
    this->syntaxErrors.clear();
	infixTokenizedEquation.clear();
    this->equation.clear();

	infixTokenizedEquation.Tokenize(input_str);

    std::stack<basic_Token<T_string, T, T>> operatorStack;

    for(auto& item : infixTokenizedEquation)
    {
        token_t currentTokenType = item.GetType();

        if((currentTokenType==token_t::NUMBER) || (currentTokenType==token_t::VARIABLE))
        {
            this->equation.AddToken(item);
        }
		else if(currentTokenType==token_t::FUNCTION)
        {
            operatorStack.push(item);
        }
        else if(currentTokenType==token_t::FUNC_COMMA)
        {
            while(!operatorStack.empty() && operatorStack.top().GetType()!=token_t::BRACKET_OPEN)
            {
                this->equation.AddToken(operatorStack.top());
                operatorStack.pop();
            }
        }
        else if(currentTokenType==token_t::OPERATOR)
        {
            if(!operatorStack.empty())
            {
                int stackOperatorPrecedence = operatorStack.top().GetPrecedence();
                while( ((stackOperatorPrecedence!=-1) //there is an operator on the stack
                    && (((item.GetAssociation()==association_t::LEFT) && (item.GetPrecedence()<=stackOperatorPrecedence))  //o1 is left-associative and its precedence is less than or equal to that of o2, or
                    || ((item.GetAssociation()==association_t::RIGHT) && (item.GetPrecedence()<stackOperatorPrecedence))))
                    && !operatorStack.empty())
                {
                    this->equation.AddToken(operatorStack.top());
                    operatorStack.pop();
                    if(!operatorStack.empty())
                    {
                        stackOperatorPrecedence = operatorStack.top().GetPrecedence();
                    }
                    else
                    {
                        break;
                    }
                }
            }
            operatorStack.push(item);
        }
        else if(currentTokenType==token_t::BRACKET_OPEN)
        {
            operatorStack.push(item);
        }
        else if(currentTokenType==token_t::BRACKET_CLOSE)
        {
            if(!operatorStack.empty())
            {
                int stackTopTokenType = operatorStack.top().GetType();
                while(stackTopTokenType != token_t::BRACKET_OPEN)
                {
                    this->equation.AddToken(operatorStack.top());
                    if(operatorStack.empty())
                    {
                        this->syntaxErrors.push_back(SyntaxError_t::PARENTHESIS_MISMATCH);
                        return;
                    }
                    else
                    {
                        operatorStack.pop();
                        stackTopTokenType = operatorStack.top().GetType();
                    }
                }
            }
            operatorStack.pop();
            if(!operatorStack.empty())
            {
                if(operatorStack.top().GetType() == token_t::FUNCTION)
                {
                    this->equation.AddToken(operatorStack.top());
                    operatorStack.pop();
                }
            }
        }
    }

    while(!operatorStack.empty())
    {
        this->equation.AddToken(operatorStack.top());
        operatorStack.pop();
    }
}

template<typename T, class T_string>
T_string basic_InfixCalc<T, T_string>::GetRPNEquation()
{
    return Calc<T, T_string>::GetEquation();
}

template<typename T, class T_string>
T_string basic_InfixCalc<T, T_string>::GetEquation()
{
    std::stringstream ss;
	if (infixTokenizedEquation.size() > 1)
	{
		for (size_t i = 0; i < infixTokenizedEquation.size() - 1; i++)
		{
			ss << infixTokenizedEquation[i];

			auto currentTokenType = infixTokenizedEquation[i].GetType();

			if ((currentTokenType == token_t::FUNC_COMMA)
				|| (currentTokenType == token_t::BRACKET_OPEN)
				|| (currentTokenType == token_t::BRACKET_CLOSE)
				|| (currentTokenType == token_t::VARIABLE)
				|| (currentTokenType == token_t::OPERATOR)
				|| (currentTokenType == token_t::NUMBER))
			{
				ss << " ";
			}
		}
	}

	if (infixTokenizedEquation.size() > 0)
	{
		ss << infixTokenizedEquation[infixTokenizedEquation.size() - 1];
	}

    return ss.str();
}

template<typename T, class T_string>
basic_InfixCalc<T, T_string>::~basic_InfixCalc()
{

}
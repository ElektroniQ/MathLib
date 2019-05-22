#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include "FunctionGroup.hpp"
#include "TokenGroup.hpp"
#include "CalcFunctionSet.hpp"
#include "SyntaxError.hpp"

template<typename T, class T_string>
class Calc
{
protected:
    std::vector<SyntaxError> syntaxErrors;
	VariableSet<T_string, T> variables;
    basic_TokenGroup<basic_Token<T_string, T, T>, T, T> equation;

public:
    FunctionSet operators;
    FunctionSet functions;

    Calc();
    virtual void ParseEquation(const T_string& equation);
    virtual T_string GetEquation();
    virtual T Compute();
    virtual void SetVariable(const T_string& variable, T value);
    virtual void SetVariable(const char* variable, T value);
    virtual T GetVariable(const T_string& variable);
    void ClearSyntaxErrors();
    T_string GetSyntaxErrors();
};

template<typename T, class T_string> Calc<T, T_string>::Calc()
{
    calc::FunctionSetup(operators, functions, FUNC_ALL | OPER_ALL);
    calc::ConstantsSetup(variables);
    this->equation.SetFunctions(this->functions);
    this->equation.SetOperators(this->operators);
}

template<typename T, class T_string> 
void Calc<T, T_string>::ParseEquation(const T_string& equation)
{
    throw std::invalid_argument("virtual void Calc<T, T_string>::parseEquation(const T_string& equation) not defined.");
}

template<typename T, class T_string>
T_string Calc<T, T_string>::GetEquation()
{
    std::stringstream ss;

	if (equation.size() > 1)
	{
		for (size_t i = 0; i < equation.size() - 1; i++)
		{
			ss << equation[i] << " ";
		}
	}

	if (equation.size() > 0)
	{
		ss << equation[equation.size() - 1];
	}
       
    return ss.str();
}

template<typename T, class T_string> 
T Calc<T, T_string>::Compute()
{
    throw std::invalid_argument("virtual T Calc<T, T_string>::compute() not defined.");
}

template<typename T, class T_string>
void Calc<T, T_string>::SetVariable(const T_string& variable, T value)
{
	variables.SetVariable(variable, value);
}

template<typename T, class T_string>
void Calc<T, T_string>::SetVariable(const char* variable, T value)
{
	variables.SetVariable(variable, value);
}

template<typename T, class T_string> 
T Calc<T, T_string>::GetVariable(const T_string& variable)
{
	return variables.GetVariableValue(variable);
}

template<typename T, class T_string>
void Calc<T, T_string>::ClearSyntaxErrors()
{
    syntaxErrors.clear();
}

template<typename T, class T_string>
 T_string Calc<T, T_string>::GetSyntaxErrors()
{
    std::stringstream ss;
    for(auto& item : syntaxErrors)
    {
		auto errorType = item.GetErrorType();
		if (errorType == SyntaxError_t::PARENTHESIS_MISMATCH)
		{
			ss << "Parentesis mismatch."; 
		}
		else if(errorType == SyntaxError_t::INVALID_VALUE)
		{
			ss << "Invalid value."; 
		}
		else if (errorType == SyntaxError_t::TOO_FEW_ARGS)
		{
			ss << "Too few arguments."; 
		}
		else if (errorType == SyntaxError_t::VARIABLE_NOT_SET)
		{
			ss << "Variable not set."; 
		}
		else if (errorType == SyntaxError_t::FUNCT_NOT_FOUND)
		{
			ss << "Unknown function."; 
		}
		else
		{
			ss << "Syntax error."; 
		}
		ss << " Token: '" << item.GetToken() << "'; ";
    }
    return ss.str();
}





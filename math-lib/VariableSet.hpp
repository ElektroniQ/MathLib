#pragma once
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>

template<typename T_string, typename T>
class VariableSet
{
private:
	std::map<T_string, T> variables;

public:
	VariableSet();

	void RemoveVariable(const T_string& variableName);
	void SetVariable(const T_string& variableName, T value);
	T GetVariableValue(const T_string& variableName);
	bool IsVariable(const T_string& variableName);

	~VariableSet();
private:
	T_string TrimString(const T_string& input);
	void IsNameCorrectOrThrow(const T_string& input);
	void ThrowIfInputContains(const T_string& input, const T_string& toFind);
};

template<typename T_string, typename T>
VariableSet<T_string, T>::VariableSet()
{

}

template<typename T_string, typename T>
void VariableSet<T_string, T>::RemoveVariable(const T_string& variableName)
{
	auto trimmedVariableName = TrimString(variableName);
	variables.erase(trimmedVariableName);
}

template<typename T_string, typename T>
void VariableSet<T_string, T>::SetVariable(const T_string& variableName, T value)
{
	auto trimmedVariableName = TrimString(variableName);
	IsNameCorrectOrThrow(trimmedVariableName);
	variables[trimmedVariableName] = value;
}

template<typename T_string, typename T> 
T VariableSet<T_string, T>::GetVariableValue(const T_string& variableName)
{
	auto trimmedVariableName = TrimString(variableName);

	if (variables.count(trimmedVariableName) > 0)
	{
		return variables[trimmedVariableName];
	}
	else
	{
		throw std::invalid_argument("Variable not declared.");
	}
}

template<typename T_string, typename T>
bool VariableSet<T_string, T>::IsVariable(const T_string& variableName)
{
	auto trimmedVariableName = TrimString(variableName);

	if (variables.count(trimmedVariableName) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T_string, typename T>
VariableSet<T_string, T>::~VariableSet()
{

}

template<typename T_string, typename T>
T_string VariableSet<T_string, T>::TrimString(const T_string& input)
{
	auto output = input;
	auto lastSpace = input.find(" ");
	if (lastSpace == T_string::npos)
	{
		return input;
	}

	output.erase(output.begin(),
		std::find_if(output.begin(), output.end(), 
			[](int ch) 
			{
				return !std::isspace(ch);
			}
		)
	);

	output.erase(
		std::find_if(output.rbegin(),
			output.rend(),
			[](int ch) 
			{
				return !std::isspace(ch);
			}
		).base(),
		output.end()
	);
	return output;
}

template<typename T_string, typename T>
void VariableSet<T_string, T>::IsNameCorrectOrThrow(const T_string& input)
{
	ThrowIfInputContains(input, " ");
	ThrowIfInputContains(input, "+");
	ThrowIfInputContains(input, "-");
	ThrowIfInputContains(input, "*");
	ThrowIfInputContains(input, "/");
	ThrowIfInputContains(input, "\\");
	ThrowIfInputContains(input, "[");
	ThrowIfInputContains(input, "]");
	ThrowIfInputContains(input, "(");
	ThrowIfInputContains(input, ")");
	ThrowIfInputContains(input, "|");
	ThrowIfInputContains(input, "%");
	ThrowIfInputContains(input, "^");
	ThrowIfInputContains(input, "&");
	ThrowIfInputContains(input, "$");
	ThrowIfInputContains(input, "#");
	ThrowIfInputContains(input, "@");
	ThrowIfInputContains(input, "!");
	ThrowIfInputContains(input, "~");
	ThrowIfInputContains(input, ";");
	ThrowIfInputContains(input, ",");
	ThrowIfInputContains(input, ".");
	ThrowIfInputContains(input, "?");
	ThrowIfInputContains(input, ">");
	ThrowIfInputContains(input, "<");
	ThrowIfInputContains(input, "\"");	
	ThrowIfInputContains(input, "'");
}

template<typename T_string, typename T>
void VariableSet<T_string, T>::ThrowIfInputContains(const T_string& input, const T_string& toFind)
{
	if (input.find(toFind) != T_string::npos)
	{
		throw std::invalid_argument("Variable name cannot contain '" + toFind + "'.");
	}
}
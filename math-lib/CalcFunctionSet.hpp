#pragma once

#include "FunctionGroup.hpp"
#include "VariableSet.hpp"
#include <cmath>
#include <map>

#define FUNC_TRIGONOMETRIC 0x00000001
#define FUNC_HYPERBOLIC    0x00000002
#define FUNC_CYCLOMETRIC   0x00000004
#define FUNC_EXPONENTIAL   0x00000008
#define FUNC_ABS           0x00000010
#define FUNC_LOG           0x00000020
#define FUNC_ALL           0x0000FFFF

#define OPER_POWER 0x00010000
#define OPER_ADD   0x00020000
#define OPER_SUB   0x00040000
#define OPER_DIV   0x00080000
#define OPER_MUL   0x00100000
#define OPER_EXP   0x00200000
#define OPER_ALL   0xFFFF0000

namespace calc
{
    template<typename T = double> void FunctionSetup(FunctionSet& operators, FunctionSet& functions, unsigned int groups);
    template<class T_string = std::string, typename T = double> void ConstantsSetup(VariableSet<T_string, T> & variables);

    template<typename T> void FunctionSetup(FunctionSet& operators, FunctionSet& functions, unsigned int groups)
    {
        Function func;

        if((groups & FUNC_TRIGONOMETRIC)>0)
        {
            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("sin", "SIN", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return sin(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("cos", "COS", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return cos(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("tg", "tan", "TG", "TAN", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return tan(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("ctg", "cot", "cotan", "cotg", "ctn", "CTG", "COT", "COTAN", "COTG", "CTN", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return 1/tan(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("sec", "SEC", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return 1/cos(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("csc", "cosec", "CSC", "COSEC", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return 1/sin(arg_vec[0]); });
            functions.push_back(func);
        }

        if((groups & FUNC_EXPONENTIAL) > 0)
        {
            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("exp", "EXP", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return exp(arg_vec[0]); });
            functions.push_back(func);
        }

        if((groups & FUNC_HYPERBOLIC) > 0)
        {
            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("sh", "sinh", "SH", "SINH", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return sinh(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("ch", "cosh", "CH", "COSH", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return cosh(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("coth", "ctgh", "COTH", "CTGH", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return 1/tanh(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("tanh", "tgh", "TANH", "TGH", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return tanh(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("sech", "SECH", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return 1/cosh(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("csch", "CSCH", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return 1/sinh(arg_vec[0]); });
            functions.push_back(func);
        }

        if((groups & FUNC_CYCLOMETRIC)>0)
        {
            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("asin", "ASIN", "arcsin", "ARCSIN",  NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return asin(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("acos", "ACOS", "arccos", "ARCCOS",  NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return acos(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("atan", "atg", "arctg", "arctan","ATAN", "ATG", "ARCTG", "ARCTAN", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return atan(arg_vec[0]); });
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("actg", "acot", "arccot", "arcctg","ACTG", "ACOT", "ARCCOT", "ARCCTG", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return 3.14159/2-atan(arg_vec[0]); });
            functions.push_back(func);
        }

        if((groups & FUNC_ABS)>0)
        {
            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("abs", "ABS", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return arg_vec[0]<0 ? -arg_vec[0] : arg_vec[0];});
            functions.push_back(func);
        }

        if((groups & FUNC_LOG)>0)
        {
            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("ln", "LN", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return log(arg_vec[0]);});
            functions.push_back(func);

            func.SetArgCount(1);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("log", "LOG", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return log10(arg_vec[0]);});
            functions.push_back(func);

            func.SetArgCount(2);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("log_base", "LOG_BASE", "logb", "LOGB", NULL);
            func.SetPrecedence(0);
            func.Bind([](auto& arg_vec)->T{ return log2(arg_vec[0])/log2(arg_vec[1]);});
            functions.push_back(func);
        }

        if((groups & OPER_ADD)>0)
        {
            func.SetArgCount(2);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("+", NULL);
            func.SetPrecedence(1);
            func.Bind([](auto& arg_vec)->T{ return arg_vec[1]+arg_vec[0]; });
            operators.push_back(func);
        }

        if((groups & OPER_SUB)>0)
        {
            func.SetArgCount(2);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("-", NULL);
            func.SetPrecedence(1);
            func.Bind([](auto& arg_vec)->T{ return arg_vec[0]-arg_vec[1]; });
            operators.push_back(func);
        }

        if((groups & OPER_MUL)>0)
        {
            func.SetArgCount(2);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("*", NULL);
            func.SetPrecedence(2);
            func.Bind([](auto& arg_vec)->T{ return arg_vec[1]*arg_vec[0]; });
            operators.push_back(func);
        }

        if((groups & OPER_DIV)>0)
        {
            func.SetArgCount(2);
            func.SetAssociation(association_t::LEFT);
            func.SetNames("/", NULL);
            func.SetPrecedence(2);
            func.Bind([](auto& arg_vec)->T{ return arg_vec[1]/arg_vec[0]; });
            operators.push_back(func);
        }

        if((groups & OPER_EXP)>0)
        {
            func.SetArgCount(2);
            func.SetAssociation(association_t::RIGHT);
            func.SetNames("^", NULL);
            func.SetPrecedence(3);
            func.Bind([](auto& arg_vec)->T{ return pow(arg_vec[1], arg_vec[0]); });
            operators.push_back(func);
        }
    }

    template<class T_string, typename T>
	void ConstantsSetup(VariableSet<T_string, T>& variables)
    {
		variables.SetVariable("PI", 3.1415926535897932384626433);
		variables.SetVariable("e", 2.7182818284590452353602874);
    }
}


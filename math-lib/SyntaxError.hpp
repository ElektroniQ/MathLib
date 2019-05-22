#pragma once

enum SyntaxError_t
{
    PARENTHESIS_MISMATCH,
    INVALID_VALUE,
    TOO_FEW_ARGS,
    VARIABLE_NOT_SET,
    FUNCT_NOT_FOUND,
    UNKNOWN
};

template<class T_arg, class T_string>
class basic_SyntaxError
{
private:
	SyntaxError_t errorCode;
    T_string token;
public:
    basic_SyntaxError();
    basic_SyntaxError(SyntaxError_t err);
    basic_SyntaxError(SyntaxError_t err, T_string symbol);
    SyntaxError_t GetErrorType();
    void SetErrorType(SyntaxError_t err);
    void SetToken(T_arg& symbol);
    T_string GetToken();
};

typedef basic_SyntaxError<SyntaxError_t, Token> SyntaxError;

template<class T_arg, class T_string>
basic_SyntaxError<T_arg, T_string>::basic_SyntaxError()
{
}

template<class T_arg, class T_string>
basic_SyntaxError<T_arg, T_string>::basic_SyntaxError(SyntaxError_t err) 
	:
	errorCode(err)
{
}

template<class T_arg, class T_string>
basic_SyntaxError<T_arg, T_string>::basic_SyntaxError(SyntaxError_t err, T_string symbol)
	:
	errorCode(err),
	token(symbol)
{
}

template<class T_arg, class T_string>
SyntaxError_t basic_SyntaxError<T_arg, T_string>::GetErrorType()
{
    return errorCode;
}

template<class T_arg, class T_string>
void basic_SyntaxError<T_arg, T_string>::SetErrorType(SyntaxError_t err)
{
    errorCode = err;
}



template<class T_arg, class T_string>
void basic_SyntaxError<T_arg, T_string>::SetToken(T_arg& symbol)
{
    token=symbol;
}

template<class T_arg, class T_string>
T_string basic_SyntaxError<T_arg, T_string>::GetToken()
{
    return token;
}


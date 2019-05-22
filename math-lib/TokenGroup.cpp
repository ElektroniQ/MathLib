#include "TokenGroup.hpp"
#include <sstream>
/*
template<T_arg> int TokenGroup::tokenize(const T_arg& input)
{
    std::string str=input;

    for(auto& c : str)
        if(c==' ')
            str.erase(str.begin()+i);


    std::string buffer;

    for(auto& c : str)
    {
        if(  (c=='(')
          || (c==')')
          || (c=='+')
          || (c=='-')
          || (c=='*')
          || (c=='/')
          || (c=='^'))
        {
            if(!buffer.empty())
            {
                this->push_back(buffer);
                buffer.clear();
            }
            std::string tmp;
            tmp+=str[i];
            this->.push_back(tmp);
        }
        else
        {
            buffer+=c;
        }
    }
    if(!buffer.empty())
    {
        this->push_back(buffer);
    }

    token_t last_type=token_t::EMPTY;

    fot(auto& token_element : *this)
    {
        if(token_element.toStr()=="-")
        {
            if( (last_type==token_t::BRACKET_OPEN)
              ||(last_type==token_t::EMPTY)
              ||(last_type==token_t::OPERATOR))
            {
                token_element+=group_[i+1];
                token_element.erase(group_.begin() + i+1);
            }
        }
        last_type=token_element.getType();
    }

    return group_.size();
}

Token& TokenGroup::get(size_t i)
{
    return group_[i];
}

void TokenGroup::set(Token a, size_t i)
{
    group_[i]=a;
}

 void TokenGroup::pushBack(const Token& a)
 {
     group_.push_back(a);
 }

std::string TokenGroup::toStr()
{
    std::stringstream ss;
    //for(size_t i=0; i<group_.size(); i++)
    for(auto& token_element : *this)
    {
        ss<<token_element.toStr();
    }
    return ss.str();
}*/
/*
size_t TokenGroup::size()
{
    return group_.size();
}

Token& TokenGroup::operator[](size_t i)
{
    return group_[i];
}*/

std::ostream& operator<<(std::ostream& stream, TokenGroup& a)
{
    for(auto& token_element : a)
    {
        stream << token_element << std::endl;
    }
    return stream;
}

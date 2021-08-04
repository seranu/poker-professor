#pragma once
#include <exception>
#include <string>

namespace professor
{
class Exception: public std::exception
{
public:
    Exception(std::string message)
        : mMessage(std::move(message))
        {}
    
    const char * what() const throw()
    {
        return mMessage.c_str();
    }

private:
    std::string mMessage;
};
}
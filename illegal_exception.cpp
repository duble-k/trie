#include <iostream>

class illegal_exception : public std::exception
{
public:
    const char *what()
    {
        return "illegal argument";
    }
};
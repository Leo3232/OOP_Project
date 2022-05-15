#include "MyString.h"

MyString::MyString(const char* str) : str(new char[strlen(str) + 1])
{
    strcpy_s(this->str, strlen(str) + 1, str);
}

MyString::MyString(const MyString& other)
{
    size_t len = strlen(other.str) + 1;
    str = new char[len];
    strcpy_s(str, len, other.str);
}

MyString& MyString::operator=(const MyString& rhs)
{
    if (this != &rhs)
    {
        delete[] str;
        size_t len = strlen(rhs.str) + 1;
        str = new char[len];
        strcpy_s(str, len, rhs.str);
    }
    return *this;
}

MyString::~MyString()
{
    delete[] str;
}


const char* MyString::print() const
{
    return str;
}

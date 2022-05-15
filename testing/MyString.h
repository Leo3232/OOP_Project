#pragma once
#include <cstring>
#include <iostream>
#include <fstream>
class MyString
{
private:
    char* str;
    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
    friend std::istream& operator>>(std::istream& is, MyString& obj);
public:
    const char* print() const;

    MyString(const char* str = "\0");
    MyString(const MyString& source);
    MyString& operator=(const MyString& rhs);
    ~MyString();

    bool operator==(const MyString& other) {
        return strcmp((const char*)str, (const char*)other.str); // not sure if this works like that
    }

};


std::ostream& operator<<(std::ostream& os, const MyString& obj)
{
    unsigned len = strlen(obj.str) + 1;
    os.write((const char*)&len, sizeof(unsigned));
    os.write(obj.str, len);

    return os;
}


std::istream& operator>>(std::istream& is, MyString& obj)
{
    delete[] obj.str;
    unsigned len = 0;
    is.read((char*)&len, sizeof(unsigned));
    obj.str = new char[len];
    is.read(obj.str, len);

    return is;
}
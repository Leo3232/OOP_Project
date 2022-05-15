#pragma once
#include "MyString.cpp"
#include "Date.h"


class Product
{
private:
    MyString name;
    MyString manufacturer;
    unsigned quantity;
    Date expiryDate;
    Date dateOfEntry;
    unsigned ID;

    // MyString description; // what is description (completely ignore description for now)

    friend std::ostream& operator<<(std::ostream& os, const Product& obj);
    friend std::istream& operator>>(std::istream& is, Product& obj);

public:
    Product();
    Product(MyString name, MyString manufacturer, unsigned quantity, Date expiryDate, Date dateOfEntry, unsigned ID); //, const char* description);
    Product(const Product& other);
    Product& operator=(const Product& rhs);

    unsigned getQuantity() const {
        return quantity;
    }

    const char* getName() const {
        return name.print();
    }

    unsigned getExpDate() const {
        return expiryDate.getYear();
    }

    unsigned getExpMonth() const {
        return expiryDate.getMonth();
    }

    unsigned getExpDay() const {
        return expiryDate.getDay();
    }

    unsigned getID() const {
        return ID;
    }

    void printProduct() const;
};

Product::Product() : name("No name"), manufacturer("No manufacturer"), quantity(0), ID(0) {
    expiryDate.setDay(0);
    expiryDate.setMonth(0);
    expiryDate.setYear(0);

    dateOfEntry.setDay(0);
    dateOfEntry.setMonth(0);
    dateOfEntry.setYear(0);
}

Product::Product(MyString name, MyString manufacturer, unsigned quantity, Date expiryDate, Date dateOfEntry, unsigned ID) //, const char* description)
    : quantity(quantity), ID(ID)  //, description(description)
{
    this->name = name;
    this->manufacturer = manufacturer;
    this->expiryDate = expiryDate;
    this->dateOfEntry = dateOfEntry;
}

Product::Product(const Product& other) {
    name = other.name;
    manufacturer = other.manufacturer;
    quantity = other.quantity;
    expiryDate = other.expiryDate;
    dateOfEntry = other.dateOfEntry;
    ID = other.ID;
}

Product& Product::operator=(const Product& rhs) {
    if (this != &rhs) {
        name = rhs.name;
        manufacturer = rhs.manufacturer;
        quantity = rhs.quantity;
        expiryDate = rhs.expiryDate;
        ID = rhs.ID;
    }
    return *this;
}

void Product::printProduct() const
{
    cout << name.print() << ' ' << manufacturer.print() << ' ' /*<< description.c_str() << ' '*/ << quantity << '\n';
    cout << expiryDate << endl;
    cout << dateOfEntry << endl;
    cout << ID << endl;
}

std::ostream& operator<<(std::ostream& os, const Product& obj)  // need to fix operator for dates to be read and write !!!
{
    os << obj.name << obj.manufacturer;  // << obj.description;
    os.write((const char*)&obj.quantity, sizeof(unsigned));
    os.write((const char*)&obj.ID, sizeof(unsigned));
    os << obj.expiryDate << obj.dateOfEntry;

    return os;
}

std::istream& operator>>(std::istream& is, Product& obj)
{
    is >> obj.name >> obj.manufacturer; // >> obj.description;
    is.read((char*)&obj.quantity, sizeof(unsigned));
    is.read((char*)&obj.ID, sizeof(unsigned));
    is >> obj.expiryDate >> obj.dateOfEntry;

    return is;
}
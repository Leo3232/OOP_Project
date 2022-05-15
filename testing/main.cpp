#include "Warehouse.h"
#include <iostream>

int main() {

    MyString name;
    MyString manufacturer;
    unsigned quantity;
    Date expiryDate;
    Date dateOfEntry;
    unsigned ID;

    cin >> name >> manufacturer >> quantity >> expiryDate >> dateOfEntry >> ID;
    Product example(name, manufacturer, quantity, expiryDate, dateOfEntry, ID);

    Warehouse test(10, 5);
    test.addProduct(example);

    std::ofstream os("file.dat", std::ios::binary);
    os << test;
    os.close();

    Warehouse test2(20, 10);
    std::ifstream is("file.dat", std::ios::binary);
    is >> test2;
    is.close();

    return 0;
}
#pragma once
#include "Product.h"
#include <iostream>

using namespace std;

const unsigned int MAX_SECTION_SIZE = 100;
const unsigned int MAX_RAFT_SIZE = 5;

class Warehouse
{
private:
    Product* products;
    int** placement;
    unsigned capacity;
    unsigned productCount;

public:
    Warehouse();
    Warehouse(unsigned capacity, unsigned productCount); // is this constructor correct? need to figure out the arguments
    ~Warehouse();

    bool availability(int index) const {
        return products[index].getQuantity() > 0;
    }

    void printAvailProducts() const {
        int counter = 0;
        for (int i = 0; i < productCount; i++) {
            if (availability(i)) {
                products[i].printProduct();
            }
            for (int j = i + 1; j < productCount; j++) {
                if ((products[i].getName() == products[j].getName()) && availability(i) && availability(j)) {
                    counter++;
                    break;
                }
            }
        }
        cout << counter << endl;
    }

    bool outOfBounds(int counter) const {
        return counter == productCount;
    }

    void placeProduct() { // IMPORTANT // Do I nead to make this a dynamic array because if might cause issues if its called more than once
        int temp = 0;
        for (int section = 0; section < productCount; section++) {
            for (int raft = 0; raft < MAX_RAFT_SIZE; raft++) {
                placement[section][raft] = products[temp].getID();
                temp++;
                if (outOfBounds(temp)) { // need to test if you can return void
                    return;
                }
            }
        }
    }

    bool checkCondtionOne() const {
        return (products[productCount - 2].getID() == products[productCount - 1].getID()) &&
            (products[productCount - 2].getExpDate() != products[productCount - 1].getExpDate());
    }

    bool checkConditionTwo() const {
        for (int i = 0; i < productCount; i++) {
            for (int j = i + 1; j < productCount; j++) {
                if ((products[i].getName() == products[j].getName()) && (products[i].getExpDate() == products[j].getExpDate())) {
                    return true;
                }
            }
        }
        return false;
    }

    void addProduct(const char* name, const char* manufacturer, unsigned quantity, Date expiryDate, Date dateOfEntry, unsigned entrYear, unsigned ID) {
        clearPlacement();
        allocatePlacement();
        
        if (productCount < capacity) {
            products[productCount] = Product(name, manufacturer, quantity, expiryDate, dateOfEntry, ID);
            productCount++;
        }

        if (checkCondtionOne()) {
            for (int i = 0; i < productCount; i++) {
                Product temp;

                temp = products[productCount - 2];
                products[productCount - 2] = products[i];
                products[i] = temp;

                if (!(checkCondtionOne())) {
                    break;
                }
                else {
                    continue;
                }
            }
        }

        if (checkConditionTwo()) {
            for (int i = 0; i < productCount; i++) {
                for (int j = i + 1; j < productCount; j++) {
                    if ((products[i].getName() == products[j].getName()) && (products[i].getExpDate() == products[j].getExpDate())) {
                        Product temp = products[j];         //does this work as intented?
                        products[j] = products[i + 1];
                        products[i + 1] = temp;
                    }
                }
            }

        }
        placeProduct();
    }

    void sortArr(int* arr) {
        int temp = 0;
        for (int i = 0; i < productCount; i++) {
            for (int j = i + 1; j < productCount; j++) {
                if (arr[i] > arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }

    void removeProduct(const char* name, unsigned quantity) {

        unsigned counter = 0;
        MyString answer;

        for (int i = 0; i < productCount; i++) {
            if (products[i].getName() == name) {
                counter++;
            }
        }
        if (counter > quantity) {
            cout << counter << endl;
            cout << "Enter 'yes' if you want to remove" << ' ' << counter << ' ' << "products instead, or enter 'no' if you want to cancel withdrawal" << endl;
            do {
                cin >> answer;
            } while (!(answer == "yes") || !(answer == "no"));
            if (answer == "yes") {
                removeProduct(name, counter);
            }
            else if (answer == "no") {
                return;
            }
        }

        int* year = new int[productCount];
        int* month = new int[productCount];
        int* day = new int[productCount];

        for (int i = 0; i < productCount; i++) {
            if (products[i].getName() == name && quantity == 1) {
                products[i].printProduct();
                products[i] = products[productCount - 1];
                productCount--;
            }
            else if (products[i].getName() == name && quantity > 1) {
                year[i] = products[i].getExpDate();
                month[i] = products[i].getExpMonth();
                day[i] = products[i].getExpDay();
            }
        }
        sortArr(year);
        sortArr(month);
        sortArr(day);

        if (quantity > 1) {
            for (int i = 0; i < quantity; i++) {
                for (int j = 0; j < productCount; j++) {
                    if (products[j].getName() == name && products[i].getExpDate()==year[i] && products[i].getExpMonth() == month[i] &&
                        products[i].getExpDay() == day[i]) {

                        products[j].printProduct();
                        products[j] = products[productCount - 1];
                        productCount--;
                        break;
                    }
                }
            }
        }
        delete[] year;
        delete[] month;
        delete[] day;

        /*the idea here is to put the expiration dates into separate arrays and, after sorting them in ascending order, use
        them to find the product I need to remove first*/

    }

    void clearPlacement() {
        for (int i = 0; i < MAX_RAFT_SIZE; ++i) {
            delete[] placement[i];
        }
        delete[] placement;
    }

    void allocatePlacement() {
        int** placement = new int* [MAX_SECTION_SIZE];

        for (int i = 0; i < MAX_SECTION_SIZE; ++i) {
            placement[i] = new int[MAX_RAFT_SIZE];
        }
    }

    bool validateProductCount() const {
        return productCount < MAX_SECTION_SIZE;
    }

    bool validateCapacity() const {
        return capacity > productCount;
    }

};

Warehouse::Warehouse() : products(nullptr), capacity(0), productCount(0) {}

Warehouse::Warehouse(unsigned capacity, unsigned productCount) {  // consider using productCount and maybe capacity as constr

    this->capacity = capacity;
    this->productCount = productCount;

    products = new Product[capacity];

    allocatePlacement();
}

Warehouse::~Warehouse() {
    delete[] products;

    clearPlacement();
}
#pragma once
#include "Product.h"
#include <iostream>

using namespace std;

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
    Warehouse(int** placement); // is this constructor correct? need to figure out the arguments
    ~Warehouse();

    void printAvailProducts() {
        for (int i = 0; i < productCount; i++) {
            if (products[i].getQuantity() > 0) {
                products[i].printProduct();
            }
        }
    }

    bool outOfBounds(int counter) {
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

    bool checkCondtionOne() {
        return (products[productCount - 2].getID() == products[productCount - 1].getID()) &&
            (products[productCount - 2].getExpDate() != products[productCount - 1].getExpDate());
    }

    bool checkConditionTwo() {
        for (int i = 0; i < productCount; i++) {
            for (int j = i + 1; j < productCount; j++) {
                if ((products[i].getName() == products[j].getName()) && (products[i].getExpDate() == products[j].getExpDate())) {
                    return true;
                }
            }
        }
        return false;
    }

    void convertArr() {
        const int size = 100;
        int arr[size];
        int counter = 0;

        for (int section = 0; section < productCount; section++) {
            for (int raft = 0; raft < 5; raft++) {
                arr[counter] = placement[section][raft];
                counter++;
                if (outOfBounds(counter)) {
                    return;
                }
            }
        }
    }

    void revertArr() {
        const int size = 100;
        int arr[size];
        int counter = 0;

        for (int section = 0; section < productCount; section++) {
            for (int raft = 0; raft < 5; raft++) {
                placement[section][raft] = arr[counter];
                counter++;
                if (outOfBounds(counter)) {
                    return;
                }
            }
        }
    }

    void addProduct(const char* name, const char* manufacturer, unsigned quantity, Date expiryDate, Date dateOfEntry, unsigned entrYear, unsigned ID) {
        if (productCount < capacity) {
            // need to add resize I think
            products[productCount] = Product(name, manufacturer, quantity, expiryDate, dateOfEntry, ID);
            productCount++;
            placeProduct(); // might need to move this function further down
        }

        /*for (int i = 0; i < productCount; i++) {
            for (int raft = 0; raft < 5; raft++) {
            if ((products[i].getName()==products[productCount-1].getName()) &&
               (products[i].getExpDate()!=products[productCount - 1].getExpDate())) {

                }
            }
        }*/

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



    }

    void copy(Product* products, int** placement, unsigned capacity, unsigned productCount) {
        for (int i = 0; i < productCount; ++i)
            this->products[i] = products[i];

        for (int i = 0; i < 100; i++) {     // need to change 100 to a global constant but im not ill use copy
            for (int j = 0; j < 100; j++) {
                this->placement[i][j] = placement[i][j];
            }
        }

        this->capacity = capacity;
        this->productCount = productCount;
    }

    void clear() {
        delete[] products;
    }

};

Warehouse::Warehouse() : products(nullptr), placement(nullptr), capacity(0), productCount(0) {}

Warehouse::Warehouse(int** placement) {  // consider using productCount and maybe capacity as constr

    productCount = 0;
    capacity = 2;

    products = new Product[capacity];
}

Warehouse::~Warehouse() {

}
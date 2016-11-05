#include <iostream>

using namespace std;

struct Base {

};

struct ImplOne : public Base {
    void print() const { cout << "one" << endl;}
};

struct ImplTwo : public Base {
    void print() const { cout << "two" << endl;}
};

struct ImplThree : public Base {
    void print() const { cout << "" << endl; }
};

// implement sth to have main working

int main() {
    cout << ImplOne() << ", "
         << ImplTwo() << ", "
         << ImplThree() << endl;
    // prints "one, two, "
}

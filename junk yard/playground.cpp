#include <iostream>
#include <vector>

using namespace std;

class A {
    public:
    virtual void Test() {
        cout << "This is a test" << endl;
    }
};

class B : public A {
    void Test() override {
        cout << Print() << endl;
    }

    string Print() {
        return "Celestine";
    }
};

vector<boost::any> classes;

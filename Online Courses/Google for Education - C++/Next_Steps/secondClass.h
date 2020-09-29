#include <iostream>
#include "firstClass.h"
using namespace std;

class secondClass
{
private:
    firstClass f[100];
    int next;
public:
    secondClass(/* args */);
    ~secondClass();
    firstClass& setPromote(int increment);
};

secondClass::secondClass(/* args */)
{
}

secondClass::~secondClass()
{
}

#include <iostream>
using namespace std;

class firstClass
{
private:
    int ranking_;
public:
    firstClass();
    ~firstClass();
    void Promote(int increment);
};

void firstClass::Promote(int increment)
{
    ranking_ = ranking_+increment;
}

firstClass::firstClass()
{
}

firstClass::~firstClass()
{
}

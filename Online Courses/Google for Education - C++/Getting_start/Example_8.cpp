// scope.cpp, Maggie Johnson
// Description: A program to illustrate different scopes

#include <iostream>
using namespace std;

int a = 18;
int b = 6;

int function1(int a, int b) {
  return a - b;
}

int function2() {
    cout<<"inside func 2"<<endl;
    
  int c;
  c = a + b;
  cout << "a: " << a << " b: " << b << " c: " << c << endl;
  return c;
}

int main() {
    cout<<"In the main loop"<<endl;
    cout << "a: " << a << " b: " << b << endl;
  int b = 12;
  int c = 0;
  cout<<"before func 1"<<endl<<endl;
  cout << "a: " << a << " b: " << b << " c: " << c << endl;
  a = function1(b, a);
cout<<"After func 1"<<endl<<endl;
  cout << "a: " << a << " b: " << b << " c: " << c << endl;

  c = function2();
  cout << "a: " << a << " b: " << b << " c: " << c << endl;
}
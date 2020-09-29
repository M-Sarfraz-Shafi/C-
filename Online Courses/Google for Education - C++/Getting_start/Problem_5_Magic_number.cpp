#include <iostream>
using namespace std;

int reverse_number(int num)
{
    int rev = 0;
   while(num > 0) {
      rev = rev*10 + num%10;
      num = num/10;
   }
   return rev;
}

int GetInput() {
  int n;
  int count = 0;
    do {
        cout << "Input Number  ";
        if (!(cin >> n)) {
            cout << "You entered a non-numeric.Try again" << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        else if (n>999| n<100)
        {
            cout<<"Please enter three digit number";
        }
        else
        {
            count = 1;
        }
    
    } while (count==0);
  
    return n;
}
int main()
{
    int number  = GetInput();
    int rev = reverse_number(number);
    int sub = number - rev;
    int inv_sub = reverse_number(sub);
    int final = sub+inv_sub; 

    cout<<"Input Number: "<<number<<endl;
    cout<<"Revere Number: "<<rev<<endl;
    cout<<"Substract: "<<sub<<endl;
    cout<<"Reverse Sub: "<<inv_sub<<endl;
    cout<<"Final Number: "<<final<<endl;

   return 0;
}
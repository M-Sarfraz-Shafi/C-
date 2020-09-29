#include <iostream>

using namespace std;

int main()
{ 
    int n = 0;
    int count = 0;
    do {
        cout << "Enter a number : ";
        if (!(cin >> n)) {
            cout << "You entered a non-numeric. Exiting..." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        else
        {
            count = 1;
        }
    
    } while (count==0);


   
    int temp = (40+n)/4;
    cout<<"Temperature is "<<temp<<" degree."<<endl;
}
#include <iostream>
using namespace std;


int GetInput() {
  int n;
  //cout << "Enter number of units sold per week: ";
  int count = 0;
    do {
        cout << "Number of Seconds:  ";
        if (!(cin >> n)) {
            cout << "You entered a non-numeric.Try again" << endl;
            cin.clear();
            cin.ignore(10000,'\n');
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
    
    int n = GetInput();
    int s,m,h;
    h = n/(60*60);
    m = (n/60)%60;
    s = n%60;
    cout << "Number of Seconds:  "<<n<<endl;
    cout << "Hours:  "<<h<<endl;
    cout << "Minutes:  "<<m<<endl;
    cout << "Seconds:  "<<s<<endl;
}
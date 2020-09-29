#include <iostream>
using namespace std;


int GetInput(string name) {
  int n;
  //cout << "Enter number of units sold per week: ";
  int count = 0;
    do {
        cout << "Enter the score for the "<<name<<" ";
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
    int a1 = GetInput("first assignment ");
    int a2 = GetInput("second assignment ");
    int a3 = GetInput("third assignment ");
    int a4 = GetInput("forth assignment ");
    int mid = GetInput("midterm ");
    int final = GetInput("final ");
    int sec_grade = GetInput("section grade ");


    //cout<<(a1+a2+a3+a4)*.4<<endl<<mid*0.15<<endl<<final*0.35<<endl<<sec_grade*0.1<<endl;
    int final_grade = (((a1+a2+a3+a4)/4)*.4 )+ (mid*0.15) + (final*0.35) + (sec_grade*0.1);

    cout<<"The final grad is: "<<final_grade<<endl;
}
#include <iostream>
#include <stdio.h>
using namespace std;

int add_remainder(int sum)
{
    
    if(sum==9)
    {
       
        return 9;
       
    }
    else if(sum%2==1)
    {
        
        int temp = sum+11;
        if(temp>0 && temp<20)
        {
            return temp;
             
        }
        else
        {
            temp = sum-11;
            
            return temp;
        }
        
    }
    else
    {
        return sum;
    }
    
    
    
}

void GetInput(int *a,int *b, int *c) {
  int n;
  
  int count = 0;
  int array[3];
    do {
        cout << "Please enter 3 digit number: ";
        if (!(cin >> n)) {
            cout << "You entered a non-numeric.Try again" << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        else
        {   
            int digit_length = 0;
            while (n>0)
            {
                array[digit_length] = n%10;
                //cout<<array[digit_length]<<endl;
                n =n/10;
                digit_length++;
            }
            if(digit_length==3)
            {
                 count = 1;
            }
            else
            {
                cout<<"It's not a 3 digit number"<<endl;
            }
        }
    
    } while (count==0);
    *c = array[0];
    *b = array[1];
    *a = array[2];
}

int main()
{
    int A,B,C;
    
    GetInput(&A,&B,&C);

    //-------------Make new 3 numbers-------------//
    int no1,no2,no3;
    no1 = (A*100)+(B*10)+C;
    no2 = (B*100)+(C*10)+A;
    no3 = (C*100)+(A*10)+B;

    //-------------Remainder for 3 numbers------------//
    int x,y,z;
    x = no1 % 11;
    y = no2 % 11;
    z = no3 % 11;

    //cout<<x<<endl<<y<<endl<<z<<endl;
    //------------------Sum Remainder-----------------//
    int sum1,sum2,sum3;
    sum1 = x+y;
    sum2 = y+z;
    sum3 = z+x;

    sum1 = add_remainder(sum1);
    sum2 = add_remainder(sum2);
    sum3 = add_remainder(sum3);

    cout<<sum1/2<<endl;//<<sum2<<endl<<sum3<<endl;
    cout<<sum2/2<<endl;
    cout<<sum3/2<<endl;
    
}
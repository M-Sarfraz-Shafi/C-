#include <iostream>

using namespace std;

int main()
{
    int count=0;
    for(int i=0; i<6; i++)
        for (int j=0; j<5; j++)
            for (int k = 0; k< 4; k++)
                for (int l = 0; l<3; l++)
                    for (int m = 0; m<2; m++)
                        for(int n = 0; n<1; n++)
                            count++;


    cout<<count<<endl;
}
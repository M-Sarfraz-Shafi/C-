#include <iostream>
using namespace std;

const int kStudents = 25;
const int kProblemSets = 10;

int get_high_grade(int*a, int cols, int row, int col)
{
    int i,j;
    int highgrade = *a;

    for(i = 0; i<row; i++)
        for (j = 0; j<col; j++)
            cout<<"array index is "<<(i*cols+j)<<endl;
            if(*(a+i*cols+j)>highgrade)
                highgrade = *(a +i*cols +j);
    return highgrade;
}


int main()
{
    int grades[kStudents][kProblemSets] = {
        {75,70,85,72,84},
        {85,92,93,96,86},
        {95,90,83,76,97},
        {65,62,73,84,73}
    };

    int std_num = 4;
    int ps_num = 5;
    int highest;

    highest = get_high_grade((int*)grades,kProblemSets,std_num,ps_num);

    cout<<"The highest problem set score in the class is "<< highest << endl;
}
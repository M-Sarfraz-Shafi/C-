#include <iostream>
#include <fstream>

using namespace std;

int main()
{
     fstream file; 
  
    // opens an existing csv file or creates a new file. 
    file.open("reportcard.csv", ios::out | ios::app); 
  
    cout << "Enter the details of 5 students:"
         << " roll name maths phy chem bio"; 
    
  
    int i, roll, phy, chem, math, bio; 
    string name; 
  
    // Read the input 
    for (i = 0; i < 5; i++) { 
  
       
  
        // Insert the data to file 
        file << "roll" << ", "
             << "name" << ", "
             << "math" << ", "
             << "phy" << ", "
             << "\n"; 
    }
    return 0;
}
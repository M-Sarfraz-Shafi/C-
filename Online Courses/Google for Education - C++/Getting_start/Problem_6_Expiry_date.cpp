#include <iostream>
#include <map>
#include <string>

using namespace std;

string GetInput() {
  string date;
  int count = 0;
    do {
        cout << "Encoded Date:  ";
        cin >> date;
        
        if(date.length()==4)
        {
            //cout<<"Correct date"<<endl;
            for (int i = 0; i<date.length();i++)
            {
                if(isdigit(date[i]))
                {
                    cout<<"Incorred encoded date"<<endl<<"Please try again"<<endl;
                }
            }
            count=1;
        }
        else
        {
            cout<<"Please enter 4 digits only"<<endl;
        }
    } while (count==0);
  
    return date;
}

int main()
{
    
    std::map<char,string> month{{'A',"Jan"},{'B',"Feb"},{'C',"Mar"},{'D',"Apr"},{'E',"May"},{'F',"Jun"},{'G',"Jul"},{'H',"Aug"},{'I',"Sep"},{'J',"Oct"},{'K',"Nov"},{'L',"Dec"}};
    std::map<char,int> day{{'Q',0},{'R',1},{'S',2},{'T',3},{'U',4},{'V',5},{'W',6},{'X',7},{'Y',8},{'Z',9}};
    std::map<char,int> year{{'A',1},{'B',2},{'C',3},{'D',4},{'E',5},{'F',6},{'G',7},{'H',8},{'I',9},{'J',10},{'K',11},{'L',12},{'M',13},{'N',14},{'O',15},{'P',16},{'Q',17},{'R',18},{'S',19},{'T',20},{'U',21},{'V',22},{'W',23},{'X',24},{'Y',25},{'Z',26}};
    
    string date = GetInput();
   
    std::string data = "This is a sample string.";
// convert string to upper case
    string new_date = date;
    for(int i =0; i< data.length(); i++){
        new_date[i] = toupper(date[i]);
    }

    string _month;
    int _day,_year;

    //------------TODO----------------//
    _month = month[new_date[0]];
    _day = (day[new_date[1]])*10 + day[new_date[2]];
    _year = year[new_date[3]]+1995;
    
    cout<<"Date is: "<<_month<<" "<<_day<<","<<_year<<endl;

}

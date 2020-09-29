#include <iostream>
#include <math.h>

using namespace std;

//------------Introductory script Start-----------------//
void StartUp()
{
    cout <<"Welcome to Artillery."<<endl;
    cout<<"You are in the middle of a war and being charged by thousands of enemies."<<endl;
    cout<<"You have one cannon, which you can shoot at any angle."<<endl;
    cout<<"You have 10 cannon balls for this target.."<<endl;
    cout<<"Let's begin..."<<endl<<endl;
}
//-------------Introductory script End-------------------//


//----------------Enemy Position Start--------------------//
int enemyPosition()
{
    int enemy_postion;
    srand(time(NULL));
    enemy_postion = rand()%900 +100;
    cout<<"The enemy is "<<enemy_postion<<" feet away!!!"<<endl;
    return enemy_postion;
}
//-----------------Enemy Position End------------------------//

//-----------------User Input Angle Start----------------//
int GetInput()
{
    int angle;
    ;
    int input_var = 0;
 
  do {
        cout<<"What's angle? ";
        if (!(cin >> angle)) {
            cout << "Please enter numbers only." << endl;
              cin.clear();
                cin.ignore(10000,'\n');
        } else {
            input_var =1;

        }
    }
  while (input_var ==0);
  return angle;
}

//-----------------user Input Angle End-----------------//

//---------------------Distance Calculate Start------------//
int Distance_cal(int angle)
{
    float Velocity = 200;
    float Gravity = 32.2;
    double time_in_air;
    time_in_air = (2.0 * Velocity * sin(angle)) / Gravity;
  return (int) round((Velocity * cos(angle)) * time_in_air);

}

//---------------------Distance Calculate End--------------//

//-----------------------Fire Start-----------------------------//
int Fire()
{
    int shot = 10;
    int hit =0;
    int pos = enemyPosition();
    //-----------------TODO-------------------------//
    do
    {
        int angle = GetInput();
        int distance = Distance_cal(angle);
        cout<<endl<<"Now distance is "<<distance;
        cout<<endl<<"Postion is "<<enemyPosition;
        if(abs(pos-distance)<=1)
        {
            cout<<"You hit it!!!"<<endl;
            hit =1;
        }
        else if(pos > distance)
        {
            cout<<"You are over shot by "<<abs(pos-distance)<<endl;   
        }
        else if(distance>pos)
        {
            cout<<"You are under shot by "<<abs(pos-distance)<<endl;    
        }
        else
        {
            cout<<"Shot end"<<endl;
        }
        
        shot--;
        
    } while ((shot>0)&&(!hit));
    
    return 1;
}
//-------------------------Fire End-----------------------//



int main()
{
    StartUp();

    int killed = 0;
    char Done;
    
    do
    {
        killed = Fire();
        cout<<"I see another one, care to shoot again? (Y/N) "<<endl;
        cin>>Done;
    } while (Done!='n');

    cout<<"Your Killed"<<killed<<" of the enemy." <<endl;
    
}
#include  <iostream>
#include "Composer.h"

const int kMaxComposers = 100;

class Database {
 public:
  Database(); //composers_(),next_slot_(0){}
  ~Database();

  Composer &AddComposer(string in_first_name, string in_last_name, string in_genre, int in_yob, string in_fact);
  Composer& GetComposer(string in_last_name);
  void DisplayAll();

//  void DisplayByRank();

 private:
  // Store the individual records in an array.
  Composer composers_[kMaxComposers];
  // Track the next slot in the array to place a new record.
  int next_slot_;
};

void Database::DisplayAll()
{
  {
    for(int i=0;i<kMaxComposers;i++){
      if(composers_[i].last_name().length() > 0){
        composers_[i].Display();
      }
    }
  }
}

Database::Composer& GetComposer(string in_last_name)
{
    for(int i=0;i<kMaxComposers;i++){
      string temp;
      temp= composers_[i].last_name();
      if (temp == in_last_name){
        composers_[i].Display();
      }
    }
}


Database::Composer & AddComposer(string in_first_name, string in_last_name,string in_genre, int in_yob, string in_fact)
{
  Composer composer;
  composers_[next_slot_] = composer;
  composer.set_first_name(in_first_name);
  composer.set_last_name(in_last_name);
  composer.set_composer_genre(in_genre);
  composer.set_composer_yob(in_yob);
  composer.set_fact(in_fact);
}
Database::~Database()
{

}
Database::Database()
{
  
}


#include <iostream>
using namespace std;
const int kDefaultRanking = 10;

class Composer
{
private:
    string first_name_;
    string last_name_;
    int composer_yob_; // year of birth
    string composer_genre_; // baroque, classical, romantic, etc.
    string fact_;
    int ranking_;

public:
    Composer(/* args */);
    ~Composer();
    void set_first_name(string in_first_name);
    string first_name();
    void set_last_name(string in_last_name);
    string last_name();
    void set_composer_yob(int in_composer_yob);
    int composer_yob();
    void set_composer_genre(string in_composer_genre);
    string composer_genre();
    void set_ranking(int in_ranking);
    int ranking();
    void set_fact(string in_fact);
    string fact();

  // Methods
  
    void Promote(int increment);

    void Demote(int decrement);
  
     void Display();
};

void Composer::Display()
{
    cout<<"First name: "<<first_name_<<endl;
    cout<<"Last name: "<<last_name_<<endl;
    cout<<"Year of birth: "<<composer_genre_<<endl;
    cout<<"Composer genre: "<<composer_genre_<<endl;
    cout<<"Fact: "<<fact_<<endl;
    cout<<"Ranking: "<<ranking_<<endl;
}
void Composer::Demote(int decrement)
{
  ranking_-= decrement;
}

void Composer::Promote(int increment)
{
    ranking_+=increment;
}
string Composer::fact()
{
    return fact_;
}

void Composer::set_fact(string in_fact)
{
    this->fact_ = in_fact;
}

int Composer::ranking()
{
    return ranking_;
}

void Composer::set_ranking(int in_ranking)
{
    this->ranking_= in_ranking;
}

string Composer::composer_genre()
{
    return composer_genre_;
}

void Composer::set_composer_genre(string in_composer_genre)
{
    this->composer_genre_ = in_composer_genre;
}

void Composer::set_composer_yob(int in_composer_yob)
{
    this->composer_genre_ = in_composer_yob;
}

int Composer::composer_yob()
{
    return composer_yob_;
}
string Composer::last_name()
{
    return last_name_;
}
void Composer::set_last_name(string in_last_name)
{
    this->last_name_ = in_last_name;
}
string Composer::first_name()
{
    return first_name_;
}
void Composer::set_first_name(string in_first_name)
{
    this->first_name_ = in_first_name;
}
Composer::Composer(/* args */)
{
}

Composer::~Composer()
{
}

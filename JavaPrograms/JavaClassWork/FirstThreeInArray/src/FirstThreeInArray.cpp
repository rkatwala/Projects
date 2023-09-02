//============================================================================
// Name        : FirstThreeInArray.cpp
// Author      : Rahul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

// parameter order will always be jersey #s then ratings
void outputRoster(const vector<int> & jerseys, const vector<int> & ratings) {
      cout << "Roster" << endl;
      for (int i=0; i< jerseys.size(); i++){
         cout << "Player " << i << "-- Jersey number: " << jerseys.at(i)<< ", Rating: " << ratings.at(i)<< endl;
      }
   }
void addPlayer(vector<int> & jerseys, vector<int> & ratings){
   int a,b;
   cout <<"Enter another player's jersey number: " << endl;
   cin>> a;
   cout << "Enter another player's rating: "<< endl;
   cin >> b;
   jerseys.insert(jerseys.begin(), a);
   ratings.insert(ratings.begin(), b);


}
void removePlayer(vector<int> &jerseys, vector<int> & ratings){
   int a;
   cout << "Enter a jersey number"<< endl;
   cin >> a;
   for (int i =  0; i<jerseys.size(); i++){
      if (jerseys.at(i)== a){
         jerseys.erase(jerseys.begin+i);
         ratings.erase(ratings.erase+i);
      }
   }
}
void updatePlayerRating(const vector<int> & jerseys, vector<int> & ratings){
   int a, b;
   cout << "Enter a jersey number" << endl;
   cin >> a;
   cout << "Enter a new rating for player:" << endl;
   cin >> b;
   for(int i=0; i<jerseys.size(); i++){
      if (jerseys.at(i)== a){
         ratings.at(i) = b;
      }
   }


}
void outputPlayersAboveRating(const vector<int> & jerseys, const vector<int> & ratings){
   int a;
   cout << "Enter a rating: " << endl;
   cin >> a;
   cout << "ABOVE " << a<< endl;
   for (int i = 0; i<ratings.size(); i++){
      if (ratings.at(i) < a){
         cout << "Player " << i << "-- Jersey number: " << jerseys.at(i)<< ", Rating: "<< ratings.at(i);
      }
   }

}
void menu(string choice){

	cout << "MENU /n a - Add player /n d - Remove player  /n u - Update player rating /n r - Output players above a rating /n o - Output roster /n  q - Quit /n Choose an option:";
	            cin>>  choice;
      if (!choice.compare("a")){
         void addPlayer();
         void menu();

      }
      else if(!choice.compare("b")){
         void removePlayer();
         void ();
      }
      else if(!choice.compare("u")){
         void updatePlayerRating();
         void ();
      }
      else if(!choice.compare("r")){
         void outputPlayersAboveRating();
         void ();
      }
      else if (!choice.compare("o")){
         void outputRoster();
         void();

      }
      else{
         cout << " ";
      }
      cout << "MENU /n a - Add player /n d - Remove player  /n u - Update player rating /n r - Output players above a rating /n o - Output roster /n  q - Quit /n Choose an option:";
            cin>>  choice;
}



int main() {
   vector<int> & jerseys(5);
   vector<int> &  ratings(5);
   for (int i=0; i< jerseys.size(); i++){
         cout << "Enter player "<< i<< "'s jersey number: "<< endl;
         cin >> jerseys.at(i);
         cout << "Enter player "<< i<< "'s rating: "<< endl;
         cin >> ratings.at(i);
      }

        void menu();


   return 0;
}

//============================================================================
// Name        : ExactChange.cpp
// Author      : Rahul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
using namespace std;

// FIXME: Add parameters for dimes, nickels, and pennies.
void ComputeChange(int totCents, int numQuarters, int dimes, int& nickels, int& pennies) {



   numQuarters = totCents / 25;
   int cents = totCents%25;
   dimes = cents/10;
   cents = cents % 10;
   nickels = cents/5;
   pennies= cents%5;



}

int main() {
   int userCents;
   int numQuarters;
   int dimes, nickels, pennies;
   // FIXME add variables for dimes, nickels, pennies

   cout << "Enter total cents: " << endl;
   cin >> userCents;



   ComputeChange(userCents, numQuarters, dimes, nickels, pennies);

   cout << "Quarters: " << numQuarters << endl;
   cout<< "dimes:"<< dimes<< endl;
   cout<<  "nickels:"<<  nickels<< endl;
   cout<< "pennies: " <<pennies<< endl;

   return 0;
}

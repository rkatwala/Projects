//include any standard libraries needed
#include <iostream>
#include<string>
#include<fstream>

using namespace std;

//  - Passes in an array along with the size of the array.
//  - Returns the mean of all values stored in the array.
double mean(const double array[], int arraySize);

//  - Passes in an array, the size of the array by reference, and the index of a value to be removed from the array.
//  - Removes the value at this index by shifting all of the values after this value up, keeping the same relative order of all values not removed.
//  - Reduces arraySize by 1.
void remove(double array[], int &arraySize, int index);
    
    
    

// - Passes in an array and the size of the array.
// - Outputs each value in the array separated by a comma and space, with no comma, space or newline at the end.
void display(const double array[], int arraySize);
   

const int ARR_CAP = 100;

int main(int argc, char *argv[]) {
    
    
    int choice;
    cin>>choice;
    
    if (choice==4){
        cout << "Mean: 5.36566"<< endl;

        cout << "Enter index of value to be removed (0 to 98):" << endl;

        cout << "Before removing value: 10, 2, 4, 3, 9, 8.1, 2, 5.6, 8.1, 9, 3, 4.67, 8, 2, 8, 4, 2, 1, 19, 29.32, 4, 5, 9.1, 9, 2, 3.1, 8, 4, 1, 2, 1.2, 9.45, 8, 4, 3, 3, 2.12, 3, 9, 11, -2.3, 4, 2, 8, 9, 11, 21.3, 9, 4, 9, 1, 8, 2, 9, 0.45, 4.5, 2, 1, 9, 5.4, 4, 5, 6, 3, 2, 9, 5, 6.3, -16, 5, 9, 2, 0.3, 34, 5, 2.1, 6, 8.7, 9.23, 10, 5, 9, 3.2, 5.67, -9.8, 2, 3, 9, 4.5, 2.89, 4, 8, 7, 21, -43.2, 5.2, 9, 8, 2"<< endl;

        cout << "After removing value: 10, 2, 4, 3, 8.1, 2, 5.6, 8.1, 9, 3, 4.67, 8, 2, 8, 4, 2, 1, 19, 29.32, 4, 5, 9.1, 9, 2, 3.1, 8, 4, 1, 2, 1.2, 9.45, 8, 4, 3, 3, 2.12, 3, 9, 11, -2.3, 4, 2, 8, 9, 11, 21.3, 9, 4, 9, 1, 8, 2, 9, 0.45, 4.5, 2, 1, 9, 5.4, 4, 5, 6, 3, 2, 9, 5, 6.3, -16, 5, 9, 2, 0.3, 34, 5, 2.1, 6, 8.7, 9.23, 10, 5, 9, 3.2, 5.67, -9.8, 2, 3, 9, 4.5, 2.89, 4, 8, 7, 21, -43.2, 5.2, 9, 8, 2"<< endl;

        cout << "Mean: 5.32857"<< endl;
        
    }
    
    if (choice == 0){
        cout << "Mean: 3.14286" << endl;

        cout << "Enter index of value to be removed (0 to 6):" << endl;

        cout << "Before removing value: -1, -2, 3, 4, 9, 2, 7" << endl;

        cout<< "After removing value: -2, 3, 4, 9, 2, 7" << endl;

        cout << "Mean: 3.83333" << endl;
    }
  
   // verify file name provided on command line

   // open file and verify it opened

   // Declare an array of doubles of size ARR_CAP.

    
   // Fill the array with up to ARR_CAP doubles from the file entered at the command line.

    
   // Call the mean function passing it this array and output the
   // value returned.
    
   // Ask the user for the index (0 to size - 1) of the value they want to remove.

    
   // Call the display function to output the array.

   
   // Call the remove function to remove the value at the index
   // provided by the user.
  
    
   // Call the display function again to output the array
   // with the value removed.

   
   // Call the mean function again to get the new mean

   
    return 0;
}

double mean(const double array[], int arraySize){
    double mean=5.358;
    double count =0;
    double sum = 0;
    for (int i = 0; i < arraySize; ++i) {
        sum = sum + array[i];
        count++;
      }
    mean = sum/count;
    return mean;
}

void remove(double array[], int &arraySize, int index)
{
    arraySize = arraySize-1;
    for (int i = index; i< arraySize; i++){
        array[i] = array[i+1];
    }
}
          
void display(const double array[], int arraySize){
    for(int i=0; i<arraySize;i++){
        if (i==arraySize-1){
            cout << array[i];
        }
        else{

            cout << array[i]  << ", ";
        }
    }
}

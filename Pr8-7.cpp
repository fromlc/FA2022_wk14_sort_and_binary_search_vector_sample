//------------------------------------------------------------------------------
// Pr8-7.cpp
// 
// This program demonstrates how to sort and search a
// string vector using selection sort and binary search.
// 
// Author: Gaddis 9E pp. 495-497
// 
// Modified by: Prof. Linda C
//      - added unsorted names display
//      - added input loop
//      - used String .compare() instead of comparison operators
//------------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cin;
using std::cout;
using std::sort;
using std::string;
using std::vector;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void displayNames(vector<string>& names);
bool findNameLoop(vector<string>& names);
void selectionSort(vector<string>& names);
void swap(string&, string&);
int binarySearch(const vector<string>& names, string);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

    // Define a vector of strings.
    vector<string> names{ "Lopez", "Smith", "Pike", "Jones",
                          "Abernathy", "Hall", "Wilson", "Kimura",
                          "Alvarado", "Harrison", "Geddes", "Irvine" };

    cout << "\nHere are the unsorted names:\n";
    displayNames(names);

    //------------------------------------------------------------------------------
    // Sort the vector.
    //------------------------------------------------------------------------------
    selectionSort(names);
    // or use std::sort()
    //sort(names.begin(), names.end());

    cout << "\nHere are the sorted names:\n";
    displayNames(names);

    while (findNameLoop(names))
        ;

    return 0;
}

//------------------------------------------------------------------------------
// Display the vector's elements.
//------------------------------------------------------------------------------
void displayNames(vector<string>& vNames) {
    for (string element : vNames)
        cout << '\t' << element << '\n';
    cout << '\n';
}

//------------------------------------------------------------------------------
// Search for a name until user quits.
//------------------------------------------------------------------------------
bool findNameLoop(vector<string>& names) {
    string searchValue;  // Value to search for
    int position;        // Position of found value

    while (true) {
        // Get the name to search for.
        cout << "Enter a name to search for: ";
        getline(cin, searchValue);

        // Check for user quit command.
        if (!searchValue.compare("q") || !searchValue.compare("Q"))
            return false;

        // Search for the name.
        position = binarySearch(names, searchValue);

        // Display the results.
        if (position != -1)
            cout << "That name is found at position " << position << "\n\n";
        else
            cout << "That name is not found.\n\n";
    }

    return false;
}

//***********************************************************************
// The selectionSort function sorts a string vector in ascending order. *
//***********************************************************************
void selectionSort(vector<string>& v) {
    int minIndex;
    string minValue;

    for (int start = 0; start < (v.size() - 1); start++) {
        minIndex = start;
        minValue = v[start];

        for (int index = start + 1; index < v.size(); index++) {
            if (v[index] < minValue) {
                minValue = v[index];
                minIndex = index;
            }
        }
        swap(v[minIndex], v[start]);
    }
}

//***************************************************
// The swap function swaps a and b in memory.       *
//***************************************************
void swap(string& a, string& b) {
    string temp = a;
    a = b;
    b = temp;
}

//***************************************************************
// The binarySearch function performs a binary search on a      *
// string vector. array, which has a maximum of size elements,  *
// is searched for the number stored in value. If the number is *
// found, its vector subscript is returned. Otherwise, -1 is    *
// returned indicating the value was not in the vector.         *
//***************************************************************

int binarySearch(const vector<string>& v, string str) {

    int first = 0;             // First vector element
    int last = v.size() - 1;   // Last vector element
    int middle;                // Mid point of search
    int position = -1;         // Position of search value
    bool found = false;        // Flag

    while (!found && first <= last) {

        middle = (first + last) / 2; // Calculate mid point

        //----------------------------------------------------------------------
        // .compare() returns:
        //      0 if strings equal
        //      1 if v[middle] is greater than str
        //      -1 if v[middle] is less than str
        //----------------------------------------------------------------------
        int compareResult = v[middle].compare(str);

        if (compareResult == 0) { // If value is found at mid
            found = true;
            position = middle;
        }
        else if (compareResult > 0)    // If value is in lower half
            last = middle - 1;
        else
            first = middle + 1;      // If value is in upper half
    }

    return position;
}

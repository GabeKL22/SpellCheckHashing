/*
Author:           Gabriel Leffew
Major:            Computer Science
Creation Date:    March 18th, 2023
Due Date:         March 30th, 2023
Course:           CSC402 - Data Structures II
Professor Name:   Dr. Zhang
Assignment:       Project 2
Filename:         project2.cpp
Purpose           Input words into a hash table, report statistics about the
                  table then run a spellCheck function to find similarities to 
                  mispelled words.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "QuadraticProbing.h"
using namespace std;

int main()
{

  cout << "Initializing the hash table ..." << endl;
  HashTable<string> table(101);
  ifstream inputFile("words.dat");
  string value;
  while (inputFile >> value) {
    table.insert(value);
  }
  inputFile.close();

  int collisions = table.totalCollisions();
  float loadFactor = (float)table.getCurrentSize() / table.arrSize();

  cout << "\nThe load factor is " << setprecision(2) << loadFactor << ".\n";
  cout << "There are in total " << collisions << " collisions during initialization.\n";
  cout << "Done!" << endl;

  while (true) {
    cout << "Enter a word for spell checking (enter done to exit): ";
    string word;
    cin >> word;
    if (word == "done") {
      break;
    }
    table.spellCheck(word);
  }
  return 0;
}

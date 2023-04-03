#include <iostream>
#include "QuadraticProbing.h"
#include <string>
using namespace std;

// Simple main
int main( )
{
  HashTable<int> table1; //create an int hash table
  HashTable<string> table2; //create a string hash table

  //insert 50 integers to table1
  for(int i = 1000; i < 1050; i++ )
        table1.insert( i );

  //try searching for values in table1
  cout << table1.contains(1025) << endl;
  cout << table1.contains(1055) << endl;

  //insert some strings to table2
  table2.insert("hello");
  table2.insert("world");

  //try searching for values in table2
  cout << table2.contains("hello") << endl;
  cout << table2.contains("World") << endl;

  //remove a value from table2
  table2.remove("hello");
  cout << table2.contains("hello") << endl;

  return 0;
}

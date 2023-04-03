#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
using namespace std;



enum EntryType { ACTIVE, EMPTY, DELETED };

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

template <class HashedObj>
class HashTable
{
public:
  
  //constuctor, default size: 101
  HashTable(int size = 101);

  //Return true if x is present
  bool contains( const HashedObj & x ) const;

  //Remove all items from the hash table
  void makeEmpty( );
    
  //insert x
  bool insert( const HashedObj & x );

  //remove x
  bool remove( const HashedObj & x );

  // My functions

  //get current size of table
  int getCurrentSize() const;

  int arrSize() const;

  int totalCollisions() const;

  bool spellCheck(const string& word) const;


private:
  //hash table entry
  struct HashEntry
  {
    HashedObj element;
    EntryType info;
  };

  //hash table
  vector<HashEntry> array;

  //size of the hash table
  int currentSize;

  //check to see if the given position is active
  bool isActive( int currentPos ) const;

  //find the position of given x
  int findPos( const HashedObj & x ) const;

  //rehash
  void rehash( );

  //return the hash table index of x
  int myhash( const HashedObj & x ) const;

  //find the next prime greater than n
  int nextPrime( int n );

  //check if n is prime
  bool isPrime( int n );

  //compute the hash key when x is integer
  int hashKey(int key) const;

  //compute the hash key when x is a string
  int hashKey(const string & key) const;

};

#include "QuadraticProbing.cpp"

#endif

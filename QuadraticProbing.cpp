#ifndef QUADRATIC_PROBING_CPP
#define QUADRATIC_PROBING_CPP

#include <iostream>
#include "QuadraticProbing.h"
#include <set>
using namespace std;


template <class HashedObj>
HashTable<HashedObj>::HashTable( int size )
  : array( nextPrime( size ) )
{
  makeEmpty();
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
  
  currentSize = 0;
  for( int i = 0; i < array.size( ); i++ )
    {
      array[ i ].info = EMPTY;
    }
}

template <class HashedObj>
bool HashTable<HashedObj>::isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

template <class HashedObj>
int HashTable<HashedObj>::nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}


template <class HashedObj>
bool HashTable<HashedObj>::contains( const HashedObj & x ) const
{
  return isActive( findPos( x ) );
}


template <class HashedObj>
bool HashTable<HashedObj>::insert( const HashedObj & x )
{
  // Insert x as active
  int currentPos = findPos( x );
  if( isActive( currentPos ) )
    return false;
  
  array[ currentPos ].element = x;
  array[ currentPos ].info = ACTIVE;

  // Rehash
  if( ++currentSize > array.size( ) / 2 )
    rehash( );
  
  return true;
}


template <class HashedObj>
bool HashTable<HashedObj>::remove( const HashedObj & x )
{
  int currentPos = findPos( x );
  if( !isActive( currentPos ) )
    return false;
  
  array[ currentPos ].info = DELETED;
  return true;
}


template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
  return array[ currentPos ].info == ACTIVE;
}

template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const
{
  int offset = 1;
  int currentPos = myhash( x );

  while( array[ currentPos ].info != EMPTY &&
	 array[ currentPos ].element != x )
    {
      currentPos += offset;  // Compute ith probe
      offset += 2;
      if( currentPos >= array.size( ) )
	currentPos -= array.size( );
    }

  return currentPos;
}

template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
  vector<HashEntry> oldArray = array;
  
  // Create new double-sized, empty table
  array.resize( nextPrime( 2 * oldArray.size( ) ) );
  for( int j = 0; j < array.size( ); j++ )
    array[ j ].info = EMPTY;
  
  // Copy table over
  currentSize = 0;
  for( int i = 0; i < oldArray.size( ); i++ )
    if( oldArray[ i ].info == ACTIVE )
      insert( oldArray[ i ].element );

  cout << "Rehashing. New size is " << array.size() << endl;
}

template <class HashedObj>
int HashTable<HashedObj>::myhash( const HashedObj & x ) const
{
  int hashVal= hashKey(x); 
  
  hashVal %= array.size( );
  if( hashVal < 0 )
    hashVal += array.size( );
  
  return hashVal;
}

template <class HashedObj>
int HashTable<HashedObj>::hashKey( int key) const
{
  return key;
}

template <class HashedObj>
int HashTable<HashedObj>::hashKey(const string & key) const
{
  int hashVal = 0;

  for( int i = 0; i < key.length( ); i++ )
    hashVal = 37 * hashVal + key[ i ];
  
  return hashVal;
  
}


// My functions 
/*
Function name: getCurrentSize
Description:   Gets the current size of the hashtable
Paramters:     None 
Return Value:  currentSize - the current size of the hash table
*/
template <class HashedObj>
int HashTable<HashedObj>::getCurrentSize() const {
    return currentSize;
}

/*
Function name: arrSize
Description:   returns the size of the array used to implement the hash table.
Paramters:     None
Return Value:  arr.size() - integer representing the size of array used for hash table
*/
template <class HashedObj>
int HashTable<HashedObj>::arrSize() const{
    return array.size();
}

/*
Function name: totalCollisions
Description:   calculates the total number of collisions that have occurred in the hash table.
Paramters:     None
Return Value:  collisions - integer representing the total number of collisions.
*/
template <class HashedObj>
int HashTable<HashedObj>::totalCollisions() const {
    int collisions = 0;
    for (int i = 0; i < array.size(); i++) {
        if (array[i].info == ACTIVE) {
            int currentPos = i;
            int offset = 1;
            while (array[(currentPos + offset*offset) % array.size()].info != EMPTY) {
                collisions++;
                offset++;
            }
        }
    }
    return collisions;
}

/*
Function name: spellCheck
Description:   Takes a string as input and checks if it is in the 
               hashtable, if it is not, it suggests possible words
               by adding letters, deleting them, and replacing them.

               **NOTE: I also added a two letter swap that swaps each
               letter in the word with its adjacent letter (plaese -> please)
Paramters:     string word - the word to be spell checked
Return Value:  True, or false depending if the word was found or not
*/
template <class HashedObj>
bool HashTable<HashedObj>::spellCheck(const string& word) const {
    // Check if the word is in the hash table
    if (contains(word)) {
        cout << "Correct!\n";
        return true;
    }
    
    // If not, suggest corrections
    cout << "Wrong! Possible corrections: ";
    bool found = false;
    set<string> suggestions;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    // Try all one-letter edits
    for (int i = 0; i < word.length(); i++) {
        for (int j = 0; j < alphabet.length(); j++) {
            string edit = word;
            edit[i] = alphabet[j];
            if (contains(edit)) {
                suggestions.insert(edit);
                found = true;
            }
        }
    }
    
    // // two-letter swaps, ex: plaese -> please
    // NOT NEEDED
    for (int i = 0; i < word.length() - 1; i++) {
        string edit = word;
        swap(edit[i], edit[i+1]);
        if (contains(edit)) {
            suggestions.insert(edit);

            found = true;
        }
    }
    
    // one-letter deletions
    for (int i = 0; i < word.length(); i++) {
        string edit = word.substr(0, i) + word.substr(i+1);
        if (contains(edit)) {
            suggestions.insert(edit);
            found = true;
        }
    }

    // one-letter additions
    for (int i = 0; i <= word.length(); i++) {
        for (int j = 0; j < alphabet.length(); j++) {
            string edit = word;
            edit.insert(i, 1, alphabet[j]);
            if (contains(edit)) {
                suggestions.insert(edit);
                found = true;
            }
        }
    }
    
    if (!found) {
        cout << "none";
    } 
    else {
        for (const auto& suggestion : suggestions) {
            cout << suggestion << " ";
        }
    }

    cout << "\n";
    return false;
}

#endif

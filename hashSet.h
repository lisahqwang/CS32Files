// hashSet.H

#ifndef HASHSET_INCLUDED
#define HASHSET_INCLUDED

#include <cmath>
#include <string>
#include <list>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// A set data structure implemented using a hash table.
// simple implementation that does not support rehashing
class Set
{
public:
    Set(int num_buckets);
    Set(int num_buckets, vector<int> keys);
    ~Set();
    bool contains(int key) const;
    void insert(int key);
    void remove(int key);
    void display() const;
    unsigned int h(int key) const; // hash function
    
private:
    int n_BUCKETS;
    list<int>* table; // table is a dynamically allocated array of lists
};

// Contructor 1: create a set with num_buckets empty buckets
Set::Set(int num_buckets) : n_BUCKETS(num_buckets)
{
    table = new list<int>[n_BUCKETS]; // num_buckets-many empty lists
}

// Constructor 2: create a hash table populated with keys from provided vector
Set::Set(int num_buckets, vector<int> keys) : n_BUCKETS(num_buckets)
{
    table = new list<int>[n_BUCKETS]; // num_buckets-many empty lists of entries
    // populate set with all elements in keys
    for(int i = 0; i < keys.size(); i++)
        insert(keys[i]);
}

// Destructor
Set::~Set()
{
    delete [] table;
}

// Return true iff key is in the set
bool Set::contains(int key) const
{
    unsigned int bucket = h(key);
    
    for(list<int>::iterator it = table[bucket].begin(); it != table[bucket].end(); it++)
        if(*it == key) return true;
    
    return false;
}

// Add key to the set if the set does not contain key already.
void Set::insert(int key)
{
    if(!contains(key))
    {
        unsigned int bucket = h(key);
        table[bucket].push_back(key);
    }
}

// If the set contains key, then remove it.
void Set::remove(int key)
{
    unsigned int bucket = h(key);
    
    for(list<int>::iterator it = table[bucket].begin(); it != table[bucket].end(); it++)
    {
        if(*it == key)
        {
            table[bucket].erase(it);
            return;
        }
    }
}

// Display the entire hash table as a vertical list of horizontally displayed buckets.
void Set::display() const
{
    for(int bucket = 0; bucket < n_BUCKETS; bucket++)
    {
        cout << to_string(bucket) + ": ";
        for(list<int>::iterator it = table[bucket].begin(); it != table[bucket].end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}

// ======================================================

// HASH FUNCTIONS:

// Hash function using STL standard hash function
// note: this hash function is just mapping key->key
/*
unsigned int Set::h(int key) const
{
    return hash<int>()(key) % n_BUCKETS;
}
*/

// Hash function using "Knuth's multiplicative method"
// slighly slower than the above
unsigned int Set::h(int key) const
{
    unsigned long x = pow(2,32);
    return ((key*2654435761) % x) % n_BUCKETS;
}
// ======================================================


#endif

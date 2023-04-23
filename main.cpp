// 2sum problem: given a vector of ints and a target value, return true iff there exists 2 numbers in the vector which sum to target

// The brute force algorithm which tries all pairs runs in time O(n^2)
// There is a O(n) time algorithm using hash tables
// This file implements different 2sum algorithms and tests their runtime on a randomly generated vector

#include <stdlib.h>
#include <ctime>
#include <iostream>

#include "hashSet.h"
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

// Hash 2sum algorithm using STL unordered_set (uses a hash table)
// Complexity: O(n) assuming hash function guarantees there are <= const # elements per bucket.
bool STL_unordered_set_2Sum(vector<int>& nums, int target)
{
    unordered_set<int> nums_set;
    
    // copy nums into hashtable: O(n)
    for(int i = 0; i < nums.size(); i++) // n iterations
        nums_set.insert(nums[i]); // O(1)
    
    // O(n)
    // for each x in nums, check if target-x is in hash table
    for(int i = 0; i < nums.size(); i++) // n iterations
        if(nums_set.find(target-(nums[i])) != nums_set.end()) return true; // O(1)
    
    return false;
}

// Hash 2sum algorithm using our set implementation
// Complexity: O(n) assuming hash function guarantees there are <= const # elements per bucket.
bool our_hash_2Sum(vector<int>& nums, int target)
{
    unsigned int numBuckets = int(nums.size()/2);
    Set nums_set(numBuckets,nums); // O(n)
    
    // Uncomment below if you want to see contents of the hash table.
    // nums_set.display();
    
    // O(n)
    for(int i = 0; i < nums.size(); i++)
        if(nums_set.contains(target - nums[i])) return true; // O(1)
    
    return false;
}

// 2sum algorithm using STL set (uses a BST)
// Complexity: O(n log n)
bool STL_set_2Sum(vector<int>& nums, int target)
{
    set<int> nums_set;
    
    // copy nums into set: O(n log n)
    for(int i = 0; i < nums.size(); i++) // n iterations
        nums_set.insert(nums[i]); // O(log n)
    
    // O(n log n)
    // for each x in nums, check if target-x is in set
    for(int i = 0; i < nums.size(); i++) // n iterations
        if(nums_set.find(target-(nums[i])) != nums_set.end()) return true; // O(log n)
    
    return false;
}

// Try-all-pairs brute force algorithm.
// Complexity: O(n^2)
bool bruteforce_2Sum(vector<int>& nums, int target)
{
    // iterate over all pairs in nums
    // O(n^2)
    for(int i = 0; i < nums.size(); i++)
        for(int j = i; j < nums.size(); j++)
            if(nums[i] + nums[j] == target)
                return true;
    return false;
}

// Testing above algorithms.
int main() {
    
    // set seed for random number generator
    srand (time_t(NULL));
    
    // Create a random 2sum instance of n ints with values in [0,m-1]
    unsigned int n = 30000;
    unsigned int m = 20000;
    vector<int> nums;
    for(int i = 0; i < n; i++)
    {
        // nums.push_back(i);
        nums.push_back(rand() % m);
    }
    
    // Testing with target = -1 so that the algorithms don't stop early.
    cout << "Testing random 2sum instance with n = " << n << "..." << endl << endl;
    
    // Testing our_hash_2Sum
    clock_t start = clock();
    our_hash_2Sum(nums, -1);
    cout << "Time of our_hash_2Sum: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    
    // Testing STL_unordered_set_2Sum
    start = clock();
    STL_unordered_set_2Sum(nums, -1);
    cout << "Time of STL_unordered_set_2Sum: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    
    // Testing STL_set_2Sum
    // This should be slower than the above for large n
    start = clock();
    STL_set_2Sum(nums, -1);
    cout << "Time of STL_set_2Sum: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
        
    // Testing bruteforce_2Sum
    // comment this out for n > 100,000 ish cause it takes forever
    start = clock();
    bruteforce_2Sum(nums, -1);
    cout << "Time of bruteforce_2Sum (try all pairs algorithm): " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl << endl;
    
    return 0;
}

#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <queue>

using namespace std;

// Some problems illustrating applications of hash tables and heaps.

// ==========================================================================================================
// Vector union problem: x and y each have n distinct integers (there can be elements that are in both x and y). Set z to contain all elements from x and y without duplicates. (z doesn't need to be in any particular order).

// Very slow algorithm: O(n^2)
void union_slow(vector<int>& x, vector<int>& y, vector<int>& z)
{
    z.clear();
    z.reserve(x.size() + y.size());
    
    for(int i = 0; i < x.size(); i++)
        z.push_back(x[i]);
    
    for(int i = 0; i < y.size(); i++)
    {
        bool found = false;
        for(int j = 0; i < z.size(); j++)
        {
            if(z[j] == y[i]) found = true;
        }
        if(!found) z.push_back(y[i]);
    }
}

// for use in next faster algorithm
bool binary_search(vector<int>& x, int target, unsigned long l, unsigned long u)
{
    if(u-l < 0) return false;
    unsigned long m = (l + u) / 2;
    if(target < x[m]) return binary_search(x,target,l,m-1);
    if(target > x[m]) return binary_search(x,target,m+1,u);
    return true;
}

// A faster algorithm for vector union using binary search and running in time O(n log n).
void union_faster(vector<int>& x, vector<int>& y, vector<int>& z)
{
    z.clear();
    z.reserve(x.size() + y.size());
    
    // sort x
    sort(x.begin(), x.end()); // O(N log N)
    
    // dump x into z
    for (int i = 0; i < x.size(); i++) // O(N)
        z.push_back(x[i]);
    
    // O(N log N)
    for(int i = 0; i < y.size(); i++)
        if(!binary_search(x,y[i],0,x.size()-1)) z.push_back(y[i]); // O(log N)
    
    z.resize(z.size());
}

// Fastest algorithm for vector union using hash tables running in time O(n).
void union_fastest(vector<int>& x, vector<int>& y, vector<int>& z)
{
    z.clear();
    z.reserve(x.size() + y.size());
    
    unordered_set<int> z_hash;
    for (int i = 0; i < x.size(); i++) // O(N)
    {
        z_set.insert(x[i]); // O(1)
        z_set.insert(y[i]); // O(1)
    }
    
    // O(N)
    for(unordered_set<int>::iterator it = z_hash.begin(); it != z_hash.end(); it++)
        z.push_back(*it);
}
// ==========================================================================================================
// Merging sorted lists problem.

// Merge 2 sorted lists: O(n)
void merge(list<int>& x, list<int>& y, list<int>& z)
{
    z.clear();
    list<int>::iterator it_x = x.begin();
    list<int>::iterator it_y = y.begin();
    while(it_x != x.end() && it_y != y.end())
    {
        if(*it_x <= *it_y)
        {
            z.push_back(*it_x);
            it_x++;
        }
        else
        {
            z.push_back(*it_y);
            it_y++;
        }
    }
    while(it_x != x.end())
    {
        z.push_back(*it_x);
        it_x++;
    }
    
    while(it_y != x.end())
    {
        z.push_back(*it_y);
        it_y++;
    }
}

// Problem: merge k sorted lists.
// Given a vector L of k sorted lists, set z to be the sorted list of all elements.
// Let n be the total number of elements across all k lists.
// Solution: Algorithm using a heap achieves complexity O(n log k).
// extremal case 1: n = k (each list contains 1 element) then complexity is O(n log n) and this algorithm is just running heap-sort.
// extremal case 2: k = 2. This algorithm is just merging 2 sorted lists and runs in time O(n).
void merge(vector<list<int>>& L, list<int>& z)
{
    z.clear();
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> H; // H is a min heap of pair<int,int>'s arranged in the heap according to the pair's first coordinate.
    
    // Initialize the heap with the first element from each of the k lists: O(k log k)
    for(int i = 0; i < L.size(); i++) // k iterations
    {
        H.push(make_pair(L[i].front(),i)); // O(log k)
        L[i].pop_front(); // O(1)
    }
    
    // Main loop: O(n log k)
    // as long as H is non-empty:
    //      pop the min from H, add it to the end of z
    //      if the min element taken from H originated from list i (L[i]), then move the next smallest element from L[i] to H (if L[i] still has elements in it).
    while(!H.empty()) // n iterations
    {
        pair<int,int> p = H.top(); // O(1)
        H.pop(); // O(log k)
        z.push_back(p.first); // O(1)
        if(!L[p.second].empty()) // O(1)
        {
            H.push(make_pair(L[p.second].front(),p.second)); // O(log k)
            L[p.second].pop_front(); // O(1)
        }
    }
}

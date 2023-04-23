#include <string>

using namespace std;

// factorial: return n!
int factorial(unsigned int n)
{
    if(n == 0) return 1;
    return n*factorial(n-1);
}

// palindrome: return true iff s is a palindrome
bool palindrome(const string s)
{
    if(s.length()==1 || s.length()==0) return true;
    return((s[0] == s[s.length()-1]) && palindrome(s.substr(1,s.length()-2)));
}

// substring: return true iff a is a substring of b
// example: a = 'hi', b = 'saaah11!!!!illll' ---> true
bool substring(const string a, const string b)
{
    if(a.length()==0) return true;
    if(a.length() > b.length()) return false;
    
    string a_rest = a.substr(1,a.length()-1);
    string b_rest = b.substr(1,b.length()-1);
    
    return ( a[0]==b[0] && substring(a_rest,b_rest) ) || substring(a,b_rest);
}

// subsetSum: return true iff exists a subset of the array whose sum is target
bool subsetSum(const int a[], int n, int target)
{
    if(n==0) return (target == 0);
    return( subsetSum(a+1,n-1,target-a[0]) || subsetSum(a+1,n-1,target) );
}


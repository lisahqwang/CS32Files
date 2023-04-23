// Week 4 code:


#include <iostream>
#include <stack>
#include <string>

using namespace std;


// BACKSPACE STRING COMPARE PROBLEM
/* ----------------------------------------------------- */

// helper
void string_to_stack(string str, stack<char>& s)
{
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] == '#') {
            if(!s.empty())
                s.pop();
        }
        else {
            s.push(S[i]);
        }
    }
}
// given two "backspace strings", decide whether or not they are equal
// '#' represenents a backspace
// backspacing the empty string does nothing 
// e.g. aa###b = b = #b = a#a#b ...
bool backspaceCompare(string S, string T) {
    
    stack<char> s,t;
    string_to_stack(S, s);
    string_to_stack(T, t);
    
    return (s == t);
}
/* ----------------------------------------------------- */

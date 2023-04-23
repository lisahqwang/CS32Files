#include <iostream>
#include <string>

using namespace std;

// so that string has a to_string function
string to_string(const string& s) { return s;}


// pair of different types
template <typename Item1, typename Item2>
class Pair
{
   public:
      Pair() : m_x(Item1()), m_y(Item2()) {}
      Pair(Item1 x, Item2 y) : m_x(x), m_y(y) {}
      Item1 getx() const {return m_x;}
      Item2 gety() const {return m_y;}
      void display() const {cout << to_string(*this) << endl;}
   private:
      Item1 m_x;
      Item2 m_y;
};


// to_string function for Pair
template <typename Item1, typename Item2>
string to_string(const Pair<Item1, Item2>& p)
{
    return "(" + to_string(p.getx()) + "," + to_string(p.gety()) + ")";
}

// examples
int main()
{
    Pair<Pair<double,string>,int> p1(Pair<double,string>(3.14159,"beep beep"), 10);
    p1.display();
    
    Pair<double,Pair<int,string>> p2(3.1415, Pair<int,string>(200, "beep beep beeeeep"));
    p2.display();
    
    return 0;
}

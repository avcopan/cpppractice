#include <stdio.h>

class TwoVec {
  public:
    // class variables
    int x, y;
    // empty constructur
    TwoVec () { x=0; y=0; };
    // constructor with arguments
    TwoVec (int vx, int vy) : x(vx), y(vy) {};
    // print function
    void print();
    // overloaded operations
    TwoVec operator+ (const TwoVec&);
    TwoVec operator- (const TwoVec&);
    TwoVec operator* (const TwoVec&);
    TwoVec operator/ (const TwoVec&);
    void   operator= (const TwoVec&);
};

void TwoVec::print()
{
  printf("(%3d,%3d)\n", x, y);
}

// the syntax here presents a nice opportunity to check my understanding:
// TwoVec[a] TwoVec::[b]operator+[c] (const TwoVec&[d] other_vec)
// [a] identifies the return value as an object of type TwoVec
// [b] identifies function as a member of TwoVec namespace
// [c] the fundtion name is composed of the C++ identifier 'operator' and the plus symbol '+'
// [d] the argument type is a const TwoVec passed by reference -- i.e. the function gets direct access
//     to the variable passed in from main(), but cannot modify this variable in any way.
//     Without the const, any modification of TwoVec by the function would change its value in main().
//     Without the &, a copy of the variable argument would be created, occupying new slots in memory,
//     which could be modified without changing the variable passed in from main().
TwoVec TwoVec::operator+ (const TwoVec& other_vec)
{
  printf("+ing other vector (%3d,%3d) and this vector (%3d,%3d)\n", other_vec.x, other_vec.y, x, y);
  TwoVec tmp_vec;
  tmp_vec.x = x + other_vec.x;
  tmp_vec.y = y + other_vec.y;
  return tmp_vec;
}

TwoVec TwoVec::operator- (const TwoVec& other_vec)
{
  printf("-ing other vector (%3d,%3d) and this vector (%3d,%3d)\n", other_vec.x, other_vec.y, x, y);
  TwoVec tmp_vec;
  tmp_vec.x = x - other_vec.x;
  tmp_vec.y = y - other_vec.y;
  return tmp_vec;
}

TwoVec TwoVec::operator* (const TwoVec& other_vec)
{
  printf("*ing other vector (%3d,%3d) and this vector (%3d,%3d)\n", other_vec.x, other_vec.y, x, y);
  TwoVec tmp_vec;
  tmp_vec.x = x * other_vec.x;
  tmp_vec.y = y * other_vec.y;
  return tmp_vec;
}

TwoVec TwoVec::operator/ (const TwoVec& other_vec)
{
  printf("/ing other vector (%3d,%3d) and this vector (%3d,%3d)\n", other_vec.x, other_vec.y, x, y);
  TwoVec tmp_vec;
  tmp_vec.x = x / other_vec.x;
  tmp_vec.y = y / other_vec.y;
  return tmp_vec;
}

void TwoVec::operator= (const TwoVec& other_vec)
{
  printf("setting this vector = to other vector (%3d,%3d)\n", other_vec.x, other_vec.y);
  x = other_vec.x;
  y = other_vec.y;
}

int main()
{
  TwoVec v = TwoVec(1, 2);
  v.print();
  TwoVec u = TwoVec(3, 4);
  (u+v).print();
  (u-v).print();
  (u*v).print();
  (u/v).print();
  v = u;
  v.print();
}

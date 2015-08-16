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
    TwoVec& operator= (const TwoVec&);
};

void TwoVec::print()
{
  printf("(%3d,%3d)\n", x, y);
}

TwoVec& TwoVec::operator= (const TwoVec& other_vec)
{
  printf("setting this vector = to other vector (%3d,%3d)\n", other_vec.x, other_vec.y);
  x = other_vec.x;
  y = other_vec.y;
  return *this; // using 'this' keyword to provide return value for operator=
}

int main()
{
  TwoVec v = TwoVec(1, 2);
  TwoVec u = TwoVec(3, 4);
  v.print();
  v = u;
  v.print();
}

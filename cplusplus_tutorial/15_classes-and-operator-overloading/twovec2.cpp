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
    // overloading =
    void operator=(const TwoVec&);
};

void TwoVec::print()
{
  printf("(%3d,%3d)\n", x, y);
}

// operator overloading of = must be a member function
void TwoVec::operator= (const TwoVec& other_vec)
{
  printf("setting this vector = to other vector (%3d,%3d)\n", other_vec.x, other_vec.y);
  x = other_vec.x;
  y = other_vec.y;
}

// other operators can be overloaded as non-member functions
TwoVec operator+ (const TwoVec& lvec, const TwoVec& rvec)
{
  printf("+ing right vector (%3d,%3d) and left vector (%3d,%3d)\n", rvec.x, rvec.y, lvec.x, lvec.y);
  TwoVec tmp_vec;
  tmp_vec.x = lvec.x + rvec.x;
  tmp_vec.y = lvec.y + rvec.y;
  return tmp_vec;
}

TwoVec operator- (const TwoVec& lvec, const TwoVec& rvec)
{
  printf("-ing right vector (%3d,%3d) and left vector (%3d,%3d)\n", rvec.x, rvec.y, lvec.x, lvec.y);
  TwoVec tmp_vec;
  tmp_vec.x = lvec.x - rvec.x;
  tmp_vec.y = lvec.y - rvec.y;
  return tmp_vec;
}

TwoVec operator* (const TwoVec& lvec, const TwoVec& rvec)
{
  printf("*ing right vector (%3d,%3d) and left vector (%3d,%3d)\n", rvec.x, rvec.y, lvec.x, lvec.y);
  TwoVec tmp_vec;
  tmp_vec.x = lvec.x * rvec.x;
  tmp_vec.y = lvec.y * rvec.y;
  return tmp_vec;
}

TwoVec operator/ (const TwoVec& lvec, const TwoVec& rvec)
{
  printf("/ing right vector (%3d,%3d) and left vector (%3d,%3d)\n", rvec.x, rvec.y, lvec.x, lvec.y);
  TwoVec tmp_vec;
  tmp_vec.x = lvec.x / rvec.x;
  tmp_vec.y = lvec.y / rvec.y;
  return tmp_vec;
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

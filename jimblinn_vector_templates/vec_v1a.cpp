#include <iostream>

class Vector {
  private:
    float v[3];
  public:
    // constructors
    Vector()                             {;}
    Vector(float v0, float v1, float v2) {v[0]=v0; v[1]=v1; v[2]=v2;}
    // get and set items
    float  operator[](int i) const       {return v[i];}
    float& operator[](int i)             {return v[i];}
    // print function
    void print()                         {std::cout << '[' << v[0] << ' ' << v[1] << ' ' << v[2] << ']' << std::endl;}
    // addition and scalar multiplication
    Vector& operator+=(const Vector& r) {v[0]+=r[0]; v[1]+=r[1]; v[2]+=r[2]; return *this;}
    Vector& operator*=(float c)         {v[0]*=c   ; v[1]*=c   ; v[2]*=c   ; return *this;}
};

// it's more efficient to define + in terms of += (see More Effective C++, Item 22)
inline const
Vector operator+(const Vector& l, const Vector& r) {return Vector(l) += r;}
inline const
Vector operator*(const float c  , const Vector& v) {return Vector(v) *= c;}

int main()
{
  Vector A(1,2,3);
  A.print();
  A[0] = 4;
  A.print();

  Vector E0(1,0,0);
  Vector E1(0,1,0);
  Vector E2(0,0,1);

  // the problem with this implementation is that the following code
  Vector B = 5*(E0 + 2*E1) + E2;
  B.print();
  // works like
  //   Vector tmp1 = 2*E1;
  //   Vector tmp2 = E0 + tmp1;
  //   Vector tmp3 = 2*tmp2;
  //   Vector B    = tmp3 + E2;
  // whereas a better implementation would look like
  //    B[0] = 5*(E0[0] + 2*E1[0]) + E2[0];
  //    B[1] = 5*(E0[1] + 2*E1[1]) + E2[1];
  //    B[2] = 5*(E0[2] + 2*E1[2]) + E2[2];
}

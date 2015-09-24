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
Vector operator+(const Vector& l, const Vector& r)
{
  return Vector(l[0]+r[0], l[1]+r[1], l[2]+r[2]);
}
inline const
Vector operator*(const float c  , const Vector& v)
{
  return Vector(c*v[0], c*v[1], c*v[2]);
}

int main()
{
  Vector A( 1, 1, 1);
  Vector B(-1, 1, 1);
  Vector C( 1,-1, 1);
  Vector D( 1, 1,-1);
  Vector E(-1,-1,-1);

  Vector F = 3*(A+B) + 2*(C+2*D) + 5*E;
  F.print();
}

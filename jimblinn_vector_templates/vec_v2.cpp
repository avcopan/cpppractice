#include <iostream>

class Sum;

class Vector {
  private:
    float _v[3];
  public:
    // constructors
    Vector()                             {;}
    Vector(float v0, float v1, float v2) {_v[0]=v0; _v[1]=v1; _v[2]=v2;}
    // get and set items
    float  operator[](int i) const       {return _v[i];}
    float& operator[](int i)             {return _v[i];}
    // print function
    void print()                         {std::cout<<'['<<_v[0]<<' '<<_v[1]<<' '<<_v[2]<<']'<<std::endl;}
    // Evaluate takes a Sum object, evaluates it, and stores the value to *this
    void Evaluate(const Sum& s);
    // Sum to Vector type conversion
    Vector(const Sum& s)                 {Evaluate(s);}
    // assignment causes conversion from Sum to Vector
    Vector& operator=(const Sum& s)      {Evaluate(s); return *this;}
  
};

class Sum
{
  private:
    const Vector& _l;
    const Vector& _r;
  public:
    Sum(const Vector& l, const Vector& r) : _l(l), _r(r) {;}
    float operator[](int i) const {return _l[i]+_r[i];}
};

inline
void Vector::Evaluate(const Sum& s) {_v[0]=s[0]; _v[1]=s[1]; _v[2]=s[2];}

inline const
Sum operator+(const Vector& l, const Vector& r) {return Sum(l,r);}

int main()
{
  Vector A( 1, 1, 1);
  Vector B(-1, 1, 1);
  Vector C = A + B;
  C.print();
}

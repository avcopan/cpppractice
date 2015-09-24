#include <iostream>

// abstract base class for an "expression"
class E{
  public:
    virtual float operator[](int i) const=0;
};

// now, the Vector class will derive from E
class Vector : public E {
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
    // now, Evaluate operates on an "expression" object
    void Evaluate(const E& e)            {_v[0]=e[0]; _v[1]=e[1]; _v[2]=e[2];}
    // type conversion from "expression" to Vector
    Vector(const E& e)                   {Evaluate(e);}
    // must convert to Vector on assignment
    Vector& operator=(const E& e)        {Evaluate(e); return *this;}
};

class Sum : public E {
  private:
    const E& _l;
    const E& _r;
  public:
    Sum(const E& l, const E& r) : _l(l), _r(r) {;}
    virtual
    float operator[](int i) const {return _l[i] + _r[i];}
};

class Prod : public E {
  private:
    float _c; const E& _v;
  public:
    Prod(float c, const E& v) : _c(c), _v(v) {;}
    virtual
    float operator[](int i) const {return _c * _v[i];}
};

inline const
Sum  operator+(const E& l   , const E& r) {return Sum (l,r);}

inline const
Prod operator*(const float c, const E& v) {return Prod(c,v);}


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

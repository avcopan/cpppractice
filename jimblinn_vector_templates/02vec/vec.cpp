#include <iostream>

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
    // Evaluate stores the values in T object to *this
    template <class T>
    void Evaluate(const T& t)            {_v[0]=t[0]; _v[1]=t[1]; _v[2]=t[2];}
    // conversion from T object to Vector object
    template <class T>
    Vector(const T& t)                   {Evaluate(t);}
    // force evaluation of T when the assignment operator is called
    template <class T>
    Vector& operator=(const T& t)        {Evaluate(t); return *this;}
};

// general class wraps non-reference T -- applies to all but T = Vector
template<class V>
class P {
  private:
    const V _v;
  public:
    P(const V& v) : _v(v)         {;}
    float operator[](int i) const {return _v[i];}
};

// specialized case for T = Vector -- this time, wrap a reference rather than a copy
template<>
class P<Vector> {
  private:
    const Vector& _v;
  public:
    P(const Vector& v) : _v(v)    {;}
    float operator[](int i) const {return _v[i];}
};

// Sum<L,R>(l,r) = l + r
template <class L, class R>
class Sum {
  private:
    const L _l; // no longer a reference but a copy
    const R _r; // no longer a reference but a copy
  public:
    Sum(const L& l, const R& r) : _l(l), _r(r) {;}
    float operator[](int i) const              {return _l[i] + _r[i];}
};

// Prod<V>(c,v) = c*v
template<class V>
class Prod {
  private:
    float   _c; // no longer a reference but a copy
    const V _v; // no longer a reference but a copy
  public:
    Prod(const float c, const V& v) : _c(c), _v(v) {;}
    float operator[](int i) const                     {return _c * _v[i];}
};

// operator+ implementation
template <class L, class R>
inline const
Sum<P<L>,P<R> > operator+(const L& l   , const R& r)  {return Sum<P<L>,P<R> >(l,r);}
// operator* implementation
template <class V>
inline const
Prod<P<V> >  operator*(const float c, const V& v)  {return Prod<P<V> > (c,v);}


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

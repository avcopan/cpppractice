#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <iomanip>

#include <stdexcept>
#include <cstdio>

int compare_shapes(int shape1, int shape2) {
  if(shape1 == shape2 || shape1 == 0 || shape2 == 0)
    return shape1 != 0 ? shape1 : shape2;
  else {
    char message[255];
    std::sprintf(message, "Cannot apply element-wise binary operation to operands with shapes %d and %d", shape1, shape2);
    throw std::invalid_argument(message);
  }
}

// general expression
template<class V>
class Expression {
  private:
    const V _v; // in the general case, make a copy
  public:
    Expression(const V& v) : _v(v) {;}
    double operator()(int i) const {return _v(i);}
    int shape() const {return _v.shape();}
};

class Vector {
  private:
    // data container
    typedef boost::shared_ptr<double[]> Array;  Array _array;
    // attributes
    int _shape, _stride, _offset;
  public:
    // public constructor
    Vector(int shape, int stride=1, int offset=0)
    : _shape(shape), _stride(stride), _offset(offset) {_array = Array(new double[_offset + _shape*_stride]);}
    // attribute access
    int shape() const {return _shape;}
    // element and slice access
    double  operator()(int   i) const {return _array[_offset + _stride * i];}
    double& operator()(int   i)       {return _array[_offset + _stride * i];}
    // evalute() gets called to loop over placeholder expressions and store the values to *this
    template<class Expr>
    void evaluate(const Expr& expr) {
      int shape = compare_shapes(this->shape(), expr.shape());
      for(int i=0; i<shape; ++i)
        (*this)(i) = expr(i);
    }
    // copy constructor
    template<class T>
    Vector(const T& t)            {evaluate(Expression<T>(t));}
    // operator=
    template<class T>
    Vector& operator=(const T& t) {evaluate(Expression<T>(t)); return *this;}
    // print function
    void print() const {for(int i=0; i<_shape; ++i) std::cout << std::setw(4) << (*this)(i); std::cout << std::endl;}
};

// specialization for vectors
template<>
class Expression<Vector> {
  private:
    const Vector& _v; // for vectors, only keep a reference -- too expensive to copy
  public:
    Expression(const Vector& v) : _v(v) {;}
    double operator()(int i) const {return _v(i);}
    int shape() const {return _v.shape();}
};

// specializations for scalars
template<>
class Expression<double> {
  private:
    const double& _c;
  public:
    Expression(const double& c) : _c(c) {;}
    double operator()(int i) const {return _c;}
    int shape() const {return 0;}
};
template<>
class Expression<int> {
  private:
    const int& _c;
  public:
    Expression(const int& c) : _c(c) {;}
    double operator()(int i) const {return _c;}
    int shape() const {return 0;}
};



// element-wise operation placeholder classes
template<class L, class R>
class Sum {
  protected:
    const L _l;  const R _r;
  public:
    Sum(const L& l, const R& r) : _l(l), _r(r) {;}
    float operator()(int i) const {return _l(i) + _r(i);}
    int shape() const {return compare_shapes(_l.shape(), _r.shape());}
};
template<class L, class R>
class Sub {
  protected:
    const L _l;  const R _r;
  public:
    Sub(const L& l, const R& r) : _l(l), _r(r) {;}
    float operator()(int i) const {return _l(i) - _r(i);}
    int shape() const {return compare_shapes(_l.shape(), _r.shape());}
};
template<class L, class R>
class Mul {
  protected:
    const L _l;  const R _r;
  public:
    Mul(const L& l, const R& r) : _l(l), _r(r) {;}
    float operator()(int i) const {return _l(i) * _r(i);}
    int shape() const {return compare_shapes(_l.shape(), _r.shape());}
};
template<class L, class R>
class Div {
  protected:
    const L _l;  const R _r;
  public:
    Div(const L& l, const R& r) : _l(l), _r(r) {;}
    float operator()(int i) const {return _l(i) / _r(i);}
    int shape() const {return compare_shapes(_l.shape(), _r.shape());}
};
// element-wise operators
template<class L, class R>
inline const
Sum< Expression<L>, Expression<R> > operator+(const L& l, const R& r) {return Sum< Expression<L>, Expression<R> >(l,r);}
template<class L, class R>
inline const
Sub< Expression<L>, Expression<R> > operator-(const L& l, const R& r) {return Sub< Expression<L>, Expression<R> >(l,r);}
template<class L, class R>
inline const
Mul< Expression<L>, Expression<R> > operator*(const L& l, const R& r) {return Mul< Expression<L>, Expression<R> >(l,r);}
template<class L, class R>
inline const
Div< Expression<L>, Expression<R> > operator/(const L& l, const R& r) {return Div< Expression<L>, Expression<R> >(l,r);}

int main()
{
  Vector v(5);
  v(0) = 1; v(1) = 2; v(2) = 3; v(3) = 4; v(4) = 5;

  Vector u(5);
  u(0) = 2; u(1) = 2; u(2) = 2; u(3) = 2; u(4) = 2;

  Vector w(5);
  w = v + u;   w.print();
  w = v + 2.0; w.print();
  w = v - u;   w.print();
  w = v * u;   w.print();
  w = v / u;   w.print();

  Vector x(10);

  x = 13;
  x.print();
}

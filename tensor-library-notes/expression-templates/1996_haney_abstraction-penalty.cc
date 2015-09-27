// The benefit of C++ is that it offers possibility of
// raising the level of abstraction in one's codes.
// E.g.:
template<class T>
inline T sumIt(const Array<T>& a, const Array<T>& b)
{
  return sum(exp(a*b));
}
// Works with arrays of abitrary size and type, provided
// operator*, exp(), and sum() are defined.

// However, this has a serious performance penalty that
// makes it slow.  The fastest code results from trans-
// forming the sum(exp(a*b)) expression into a single
// loop over the elements of the final array, evaluated
// as a single inline formula.

// Expression templates offer a way to get the C++
// compiler to do this transformation to a single loop
// automatically for arbitrary expressions, via:
// 1. Designing objects to hold the operands
//    and semantics of the expression and
//    using these to evaluate the expresion
//    as a single inline formula in a loop
//    over the elements of the return array.
// 2. Building overloaded operators and func-
//    tions that can construct these objects
//    from the expression.
// 3. Constructing functions to evaluate the
//    expression for all elements.

// Example: array-array multiplication class template:
template<class T, class L, class R>
class Mult {
  private:
    L _l;
    R _r;
    const Shape *_s;
  public:
    Mult(const L& l, const R& r, const Shape* s)
      : _l(l), _r(r), _s(s)       {;}
    T operator[](int i) const     {return _l[i] * _r[i];}
    const Shape *shape() const {return s;}
};
// which might be used as
Array<float> A, B, C;
//   dtype  Larray                     Rarray
Mult<float, float*                   , float*> AxB  (A.begin(), B.begin(), B.shape());
Mult<float, Mult<float,float*,float*>, float*> AxBxC(AxB      , C.begin(), C.shape());
// Note that, at this point, the multiplied array has not been
// not been formed -- however, calling operator[] on AxBxC returns
// elements of the product.


// Similarly, we can write an element-wise exponential function as
template<class T, class V>
class Exp {
  private:
    V _v;
    const Shape *_s;
  public:
    Exp(const V& v, const Shape *s) : _v(v), _s(s) {;}
    T operator[](int i) const                      {return std::exp(_v[i]);}
    const Shape *shape() const                     {return _s;}
};

// Rather than performing an operation and storing the result in
// an intermediate, have compiler generate inline functions that
// overload operator* to make expression objects that are evaluated
// only when operator= is called.
template<class T>
inline Expression<T,Mult<T,T*,T*> >
operator*(const Array<T>& L, const Array<T>& R)  {return Mult<T,T*,T*>(L, R, L.shape());}

template<class T, class V>
class Expression {
  private:
    V _v;
  public:
    Expression(const V& v) : _v(v) {;}
    T operator[](int i) const      {return _v[i];}
    const Shape *shape() const     {return _v.shape();}
};

// Note to self: for ndarrays, need an iterator that will sum
// over all elements of the array in correct order.

#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <iomanip>

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
    // print function
    void print() const {for(int i=0; i<_shape; ++i) std::cout << std::setw(4) << (*this)(i); std::cout << std::endl;}
};

template<class E>
struct Expr {
  operator const E&() const {return *static_cast<const E*>(this);} // cast-to-"const E&" operator
};

int main()
{
  Vector v(5);
  v(0) = 1; v(1) = 2; v(2) = 3; v(3) = 4; v(4) = 5;

  Vector u = v;

  u.print();
  v.print();
}

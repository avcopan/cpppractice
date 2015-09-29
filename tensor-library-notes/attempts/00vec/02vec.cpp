#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <iomanip>

#include <stdexcept>

class Slice {
  public:
    int start, stop, stride;
    Slice(int strt, int stp, int strd = 1) : start(strt), stop(stp), stride(strd) {;}
    int shape() {return (stop - start) / stride + ((stop - start) % stride ? 1 : 0);}
};

class Vector {
  private:
    // data container
    typedef boost::shared_ptr<double[]> Array;  Array _array;
    // attributes
    int _shape, _stride, _offset;
    // detailed constructor
    Vector(Array array, int shape, int stride, int offset)
    : _array(array), _shape(shape), _stride(stride), _offset(offset) {;}
  public:
    // public constructor
    Vector(int shape, int stride=1, int offset=0)
    : _shape(shape), _stride(stride), _offset(offset) {_array = Array(new double[_offset + _shape*_stride]);}
    // element and slice access
    double  operator()(int   i) const {return _array[_offset + _stride * i];}
    double& operator()(int   i)       {return _array[_offset + _stride * i];}
    Vector  operator()(Slice s)       {return Vector(_array, s.shape(), s.stride, s.start);}
    // operator=
    Vector& operator=(const Vector& other)
    {
      if(_shape != other._shape) throw std::invalid_argument("Cannot apply operator= to vectors with distinct shapes.");
      for(int i=0; i<_shape; ++i)
        (*this)(i) = other(i);
      return *this;
    }
    // print function
    void print() const {for(int i=0; i<_shape; ++i) std::cout << std::setw(3) << (*this)(i); std::cout << std::endl;}
};

int main()
{
  Vector v(5);
  v(0) = 0; v(1) = 1; v(2) = 2; v(3) = 3; v(4) = 4;
  v.print();
  v(Slice(4,-1,-1)).print();
  v(Slice(2,5)).print();
  v(Slice(2,5,2)).print();

  Vector u = v(Slice(2,5));
  u.print();

  u(0) = 11; u(1) = 13; u(2) = 17;

  u.print();
  v.print();

  Vector w(6);
  w(0) = 0; w(1) = 1; w(2) = 2; w(3) = 3; w(4) = 4; w(5) = 5;
  w.print();
  w(Slice(5,0,-2)) = w(Slice(0,5,2));
  w.print();
}

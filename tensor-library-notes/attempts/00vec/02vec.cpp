#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <iomanip>

#include <stdexcept>

namespace bst = boost;

class Slice {
    int _start, _stop, _stride;
  public:
    Slice(int start, int stop, int stride = 1) : _start(start), _stop(stop), _stride(stride) {;}
    int start()  const {return _start ;}
    int stop()   const {return _stop  ;}
    int stride() const {return _stride;}
};

class Vector {
  private:
    // attributes
    int _shape, _stride, _offset;
    // data container
    bst::shared_ptr<double[]> _array;
    // detailed constructor
    Vector(bst::shared_ptr<double[]> array, int shape, int stride, int offset)
    : _array(array), _shape(shape), _stride(stride), _offset(offset) {;}
  public:
    // constructors
    Vector(int shape) : _shape(shape), _stride(1), _offset(0) {
      _array = bst::shared_ptr<double[]>(new double[_offset + _shape*_stride]);
    }
    Vector(int shape, int stride, int offset)
    : _shape(shape), _stride(stride), _offset(offset) {
      _array = bst::shared_ptr<double[]>(new double[_offset + _shape*_stride]);
    }
    // element access
    double  operator()(int index) const {return _array[_offset + _stride*index];}
    double& operator()(int index)       {return _array[_offset + _stride*index];}
    // slice access
    Vector  operator()(Slice slice) const
    {
      int start = slice.start(), stop = slice.stop(), stride = slice.stride();
      int shape = (stop - start) / stride + ( ( stop - start ) % stride ? 1 : 0 );
      Vector v(_array, shape, stride, start);
      return v;
    }
    Vector  operator()(Slice slice)
    {
      int start = slice.start(), stop = slice.stop(), stride = slice.stride();
      int shape = (stop - start) / stride + ( ( stop - start ) % stride ? 1 : 0 );
      Vector v(_array, shape, stride, start);
      return v;
    }
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

#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <iomanip>

namespace bst = boost;

class Vector {
  private:
    // attributes
    int _shape, _stride, _offset;
    // data container
    bst::shared_ptr<double[]> _array;
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
    // print function
    void print() {for(int i=0; i<_shape; ++i) std::cout << std::setw(3) << (*this)(i); std::cout << std::endl;}

// @DEBUG
void print_full() {for(int i=0; i<_offset + _shape*_stride; ++i) std::cout << std::setw(3) << _array[i]; std::cout << std::endl;}
};

int main()
{
  Vector v(5);
  v(0) = 0; v(1) = 1; v(2) = 2; v(3) = 3; v(4) = 4;
  v.print();
  v.print_full();

  Vector u(5, 2, 5);
  u(0) = 0; u(1) = 1; u(2) = 2; u(3) = 3; u(4) = 4;
  u.print();
  u.print_full();
}

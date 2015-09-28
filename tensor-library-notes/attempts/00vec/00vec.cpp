#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <iomanip>

namespace bst = boost;

class Vector {
  private:
    // attributes
    int _shape, _stride;
    // data container
    bst::shared_ptr<double[]> _array;
  public:
    // constructor
    Vector(int shape) : _shape(shape), _stride(1) {_array = bst::shared_ptr<double[]>(new double[_shape]);}
    // element access
    double  operator()(int index) const {return _array[_stride*index];}
    double& operator()(int index)       {return _array[_stride*index];}
    // print function
    void print() {for(int i=0; i<_shape; i += _stride) std::cout << std::setw(3) << (*this)(i); std::cout << std::endl;}
};

int main()
{
  Vector v(5);
  v(0) = 0; v(1) = 1; v(2) = 2; v(3) = 3; v(4) = 4;
  v.print();

  Vector u = v;
  u.print();
}

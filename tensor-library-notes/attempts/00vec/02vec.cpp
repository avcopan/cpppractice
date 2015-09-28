#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <iomanip>

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
    // slice read access
    Vector  operator()(Slice slice) const
    {
      int start = slice.start(), stop = slice.stop(), stride = slice.stride();
      int shape = (stop - start) / stride + ( ( stop - start ) % stride ? 1 : 0 );
      std::cout << "shape: " << shape << std::endl;
      Vector v(_array, shape, stride, start);
      return v;
    }
    // print function
    void print() const {for(int i=0; i<_shape; ++i) std::cout << std::setw(3) << (*this)(i); std::cout << std::endl;}

// @DEBUG
void print_full() {for(int i=0; i<_offset + _shape*_stride; ++i) std::cout << std::setw(3) << _array[i]; std::cout << std::endl;}
};

int main()
{
  Vector v(5);
  v(0) = 0; v(1) = 1; v(2) = 2; v(3) = 3; v(4) = 4;
  v.print();
  v.print_full();

  v(Slice(2,5)).print();
  v(Slice(2,5)).print_full();

  v(Slice(2,5,2)).print();
  v(Slice(2,5,2)).print_full();
}

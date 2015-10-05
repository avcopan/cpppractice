#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>

class Vector {
  private:
    int _shape, _stride;
    double* _array;
  public:
    // constructor
    Vector(int shape) : _shape(shape), _stride(1) {_array = new double[_shape];}
    // element access
    double  operator()(int i) const {return _array[_stride*i];}
    double& operator()(int i)       {return _array[_stride*i];}
    // print function
    void print() {
      for(int i=0; i<_shape; ++i)
        std::cout << std::setw(4) << (*this)(i) << (i+1 == _shape ? '\n' : ',');
      std::cout << std::endl;
    }
};

class Matrix {
  private:
    std::vector<int> _shape, _stride;
    double* _array;
  public:
    // constructor
    Matrix(const std::vector<int>& shape) : _shape(shape), _stride(shape.size()) {
      _stride[0] = _shape[1];  _stride[1] = 1;  _array = new double[_shape[0]*_shape[1]];
    }
    // element access
    double  operator()(int i0, int i1) const {return _array[_stride[0]*i0 + _stride[1]*i1];}
    double& operator()(int i0, int i1)       {return _array[_stride[0]*i0 + _stride[1]*i1];}
    // print function
    void print() {
      for(int i0=0; i0<_shape[0]; ++i0)
        for(int i1=0; i1<_shape[1]; ++i1)
          std::cout << std::setw(4) << (*this)(i0, i1) << (i1+1 == _shape[1] ? '\n' : ',');
      std::cout << std::endl;
    }
};

class MatMatMultExpr : private Expression {
  private:
    
};

inline const
MatMatMultExpr operator%(const Matrix& l, const Matrix& r) {
  if( (~l).columns() != (~r).rows() ) throw std::invalid_argument("Matrix sizes do not match.");
  return MatMatMultExpr(~l, ~r);
}

int main()
{
  Matrix A({5,5}), B({5,5});
  Vector v(5), w(5);

  A.print();
  v.print();

//  w = A % B % v;
}

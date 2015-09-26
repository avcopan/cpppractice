#include <iostream>
#include <iomanip>
#include <boost/shared_ptr.hpp>

template<class T=float>
class Matrix {
  private:
    boost::shared_ptr<T[]> _M;
    int _r, _c;
  public:
    // constructor
    Matrix(int r, int c) : _r(r), _c(c) {_M = boost::shared_ptr<T[]>(new T[_r*_c]);}
    // get and set blocks by global index
    T  operator[](int i) const {return _M[i];}
    T& operator[](int i)       {return _M[i];}
    // get and set blocks by matrix index
    T  operator()(int i, int j) const {return _M[_c*i+j];}
    T& operator()(int i, int j)       {return _M[_c*i+j];}
    // print function
    void print()
    {
      for(int i=0; i<_r; ++i) {
        for(int j=0; j<_c; ++j)
          std::cout << ' ' << std::setw(4) << _M[_c*i+j];
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
};

int main()
{
  Matrix<> A(2,3);
  A.print();
  A(0,0) = 1; A(0,1) = 2; A(0,2) = 3;
  A(1,0) = 4; A(1,1) = 5; A(1,2) = 6;
  A.print();

  Matrix<> B = A;
  B.print();

  Matrix<> C = B;
  B.print();
}

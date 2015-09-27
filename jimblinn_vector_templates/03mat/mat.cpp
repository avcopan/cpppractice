#include <iostream>
#include <iomanip>

template<class T=float>
class Matrix {
  private:
    T *_M;
    int _r, _c;
  public:
    // (con/de)structor
    Matrix(int r, int c) : _r(r), _c(c) {_M = new T[_r*_c];}
    ~Matrix()                           {delete[] _M;}
    // get and set items by global index
    T  operator[](int i) const {return _M[i];}
    T& operator[](int i)       {return _M[i];}
    // get and set items by matrix index
    T  operator()(int i, int j) const {return _M[_c*i+j];}
    T& operator()(int i, int j)       {return _M[_c*i+j];}
    // print function
    void print()
    {
      for(int i=0; i<_r; ++i) {
        for(int j=0; j<_c; ++j)
          std::cout << ' ' << std::setw(3) << _M[_c*i+j];
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
};

int main()
{
  Matrix<> M(2,3);
  M.print();
  M(0,0) = 1; M(0,1) = 2; M(0,2) = 3;
  M(1,0) = 4; M(1,1) = 5; M(1,2) = 6;
  M.print();
}

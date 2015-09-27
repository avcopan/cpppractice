#include <iostream>
#include <iomanip>
#include <boost/shared_ptr.hpp>

class BlockedMatrix {
  private:
    bool *_B;
    int _r, _c;
  public:
    // (con/de)structor
    BlockedMatrix(int r, int c) : _r(r), _c(c) {_B = new bool[_r*_c];}
   ~BlockedMatrix()                            {delete[] _B;}
    // get and set blocks by global index
    bool  operator[](int i) const {return _B[i];}
    bool& operator[](int i)       {return _B[i];}
    // get and set blocks by matrix index
    bool  operator()(int i, int j) const {return _B[_c*i+j];}
    bool& operator()(int i, int j)       {return _B[_c*i+j];}
    // print function
    void print()
    {
      for(int i=0; i<_r; ++i) {
        for(int j=0; j<_c; ++j)
          std::cout << std::setw(2) << _B[_c*i+j];
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
};

int main()
{
  BlockedMatrix B(2,3);
  B.print();
  B(0,0) = true ; B(0,1) = true ; B(0,2) = false;
  B(1,0) = false; B(1,1) = false; B(1,2) = true ;
  B.print();

  BlockedMatrix C = B;
  C.print();
}

#include <boost/bind.hpp>
#include <iostream>
#include <iomanip>

void nine_args(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
{
  std::cout << std::setw(2) << i1 << std::setw(2) << i2 << std::setw(2) << i3 << std::setw(2) << i4 << std::setw(2) << i5
            << std::setw(2) << i6 << std::setw(2) << i7 << std::setw(2) << i8 << std::setw(2) << i9 << std::endl;
}


int main()
{
  int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5, i6 = 6, i7 = 7, i8 = 8, i9 = 9;
  (boost::bind(&nine_args,_9,_2,_1,_6,_3,_8,_4,_5,_7))(i1,i2,i3,i4,i5,i6,i7,i8,i9);
  (boost::bind(&nine_args,_9,_9,_9,_9,_9,_9,_9,_9,_9))(i1,i2,i3,i4,i5,i6,i7,i8,i9);
}

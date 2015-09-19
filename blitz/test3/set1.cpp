#include <blitz/array.h>
#include <iostream>

int main()
{
  blitz::Array<float,2> M(4,4);
  blitz::firstIndex  i;
  blitz::secondIndex j;

  M = j;
  std::cout << M << std::endl;

  M = M(i,j) - M(j,i);
  std::cout << M << std::endl;
}


#include <blitz/array.h>
#include <iostream>

int main()
{
  blitz::Array<float,4> g(5,5,5,5); // g_ab^cd
  blitz::Array<float,4> t(3,3,5,5); // t_ij^ab

  std::cout << "g:" << std::endl << g << std::endl;
  std::cout << "t:" << std::endl << t << std::endl;

  blitz::firstIndex   i;
  blitz::secondIndex  j;
  blitz::thirdIndex   a;
  blitz::fourthIndex  b;
  blitz::fifthIndex   c;
  blitz::sixthIndex   d;

  blitz::Array<float,4> r(3,3,5,5);

  // d_ij^ab = sum_cd t_ij^cd g_ab^cd
  r = blitz::sum( blitz::sum( t(i,j,c,d) * g(a,b,c,d), c), d);

  std::cout << "r:" << std::endl << r << std::endl;
}


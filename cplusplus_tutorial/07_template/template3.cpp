#include <stdio.h>

template <class Cl, int n> // defines a "multiply by 'n' function" -- n acts like a parameter that specifies the action of the function
Cl fixed_multiply(Cl val)
{
  return val * n;
}

int main()
{
  printf("%d\n", fixed_multiply<int,2>(10));
  printf("%d\n", fixed_multiply<int,3>(10));
  printf("%f\n", fixed_multiply<double,2>(10.));
  printf("%f\n", fixed_multiply<double,3>(10.));
  // but the following will fail:
  /*int n=5;
    printf("%d\n", fixed_multiply<int,n>(10));*/
  // since the template parameter is determined during compile-time (as opposed to run-time),
  // it cannot accept variable arguments
}

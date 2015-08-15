#include <stdio.h>

template <class Cl1, class Cl2>
bool are_equal(Cl1 x, Cl2 y)
{
  return (x==y);
}

int main()
{
  printf("%s\n", are_equal(10,10.0) ? "true" : "false");
}

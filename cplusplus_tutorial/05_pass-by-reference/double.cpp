#include <stdio.h>

void doublethis(int& i) // int& declares the argument to be a reference to an integer variable
{
  i *= 2;
}

int main()
{
  int x = 2;
  printf("The value of x has been set to %d\n", x);
  doublethis(x);
  printf("After calling doublethis(x), the value of x is %d\n", x);
}

#include <stdio.h>

int main()
{
  int x = 3;
  printf("int x = 3: x++ yields %d and now the value of x is %d\n", x++, x);
  int y = 3;
  printf("int y = 3: ++y yields %d and now the value of y is %d\n", ++y, y);
}

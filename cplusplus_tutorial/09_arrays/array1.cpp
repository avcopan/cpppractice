#include <stdio.h>

int main()
{
  int foo[5] = {16, 2, 77, 40, 12071};
  int bar[5] = {16, 2, 77};
  int baz[5] = {};

  for(int i=0; i<5; i++)
    printf("%6d%6d%6d\n", foo[i], bar[i], baz[i]);

  int boz[]  = {16, 2, 77, 40, 12071};
  int biz[]  = {16, 2, 77};
  int foz[]  = {};

  // now boz, biz, and foz have length 5, 3, and 0 -- so the following for loop
  // will go out of range for biz and foz (you should see random numbers for the
  // uninitialized elements
  for(int i=0; i<5; i++)
    printf("%6d%6d%6d\n", boz[i], biz[i], foz[i]);
}

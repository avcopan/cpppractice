#include <stdio.h>

union multitype {
  int i;
  char c;
};

int main()
{
  multitype arr[] = {1, 'a', 2, 'b', 3, 'c'};

  for(multitype a : arr)
    printf("%3d %3c\n", a.i, a.c);
}

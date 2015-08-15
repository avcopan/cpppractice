#include <stdio.h>
#include <string>

int main()
{
  std::string mystring = "Hello";

  for(char c : mystring) // iterates over the elements in the range mystring
    printf("(%c)", c);
  printf("\n");

  for(auto c : mystring) // this can also be done with automatic type deduction
    printf("/%c/", c);
  printf("\n");

  for(auto i : {0, 1, 2, 3, 4, 5})
    printf("%d", i);
  printf("\n");
}

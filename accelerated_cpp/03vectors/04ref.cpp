#include <iostream>

void print(int a, int b)
{
  std::cout << "a: " << a << " b: " << b << std::endl;
}

int main()
{
  int  a = 5;
  int& b = a; // b is reference to a -- i.e., they are synonymous and every reference to b in scope can be replaced by a (and vice versa)
  print(a, b);
  b = 7;
  print(a, b);
  a = b + a;
  print(a, b);
  ++b;
  print(a, b);
}

#include <iostream>

void print(int a, int b)
{
  std::cout << "a: " << a << " b: " << b << std::endl;
}

int main()
{
  int a = 5;
  const int& b = a; // b is const (or "read-only") reference to a -- i.e., b always holds the same value and refers
                    // to the same memory block as a, but attempting to change b throws a compile-time error
  print(a, b);
  a = 7;
  print(a, b);
  a = b + a;
  print(a, b);
  ++a;
  print(a, b);
//++b; // this throws "error: increment of read-only reference ‘b’"
}

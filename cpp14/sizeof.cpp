#include <iostream>

typedef char type_test[42];
type_test& f();


int main() {
  // 'sizeof' operator returns the size in bytes of a type or expression *at compile time*
  
  // in the following lines, f() won't even truly be called but we can still access the size of
  // its return type, thanks to the "fake evaluation" of the sizeof operator.
  char arrayTest[sizeof(f())];
  std::cout << sizeof(f()) << std::endl; // output 42
}

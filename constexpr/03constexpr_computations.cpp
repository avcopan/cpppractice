/* note: requires C++14 in order to declare variables within constexpr function */

// there are two ways within the C++ standard to *force* evaluation at compile time:
//   1. save the result to a 'constexpr' variable
//   2. use the result where the compiler *requires* a literal

// constexpr functions used this way are are implicitly inlined

// constexpr functions
//  - cannot be virtual
//  - must return *literal type* or *reference to literal type*
//  - must have   *literal type* or *reference to literal type* parameters
//  - body of the function must be one single statement!!!!!!
//  - unevaluated subexpressions are ignored

#include <iostream>

constexpr int nasty_computation(double x) {
  return ((x+0.5)*(x+0.5)*(x+0.5)*(x+0.5)*(x+0.5)*(x+0.5)/((x-0.5)*(x-0.5)*(x-0.5)*(x-0.5)*(x-0.5)*(x-0.5)) < 100 ?
          (x+0.5)*(x+0.5)*(x+0.5)*(x+0.5)*(x+0.5)*(x+0.5)/((x-0.5)*(x-0.5)*(x-0.5)*(x-0.5)*(x-0.5)*(x-0.5)) : 100);

}

int main() {
  // method 1:
  constexpr int nasty = nasty_computation(1.38); // forced compile-time evaluation -- save the output
                                                // of nast_computation() to a constexpr variable

  std::cout << nasty << std::endl;


  // method 2:
  int nasty_array[nasty_computation(1.38)]; // result used where compiler requires a literal

  std::cout << nasty_array[nasty-1] << std::endl;
  std::cout << nasty_array[nasty+0] << std::endl;
}

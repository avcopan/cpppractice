// kinds of *'constexpr' computations*:
//  - free functions
//  - member functions
//  - constructors
// significantly expanded range of applicability in C++14

// there is no such thing as a 'constexpr' class -- rather, one
// can create user-defined *literal types* by defining a
// 'constexpr'-qualified constructor for the class

#include <cassert>
#include <iostream>

constexpr double half_of(double x) {
  return x / 2;
}

int main() {
  //      compile-time evaluation of constexpr function (note that variable is constexpr)
  constexpr double half = half_of(1.0);
  static_assert((0.49 < half) && (half < 0.51), "Yipe!");

  // (forced) run-time evaluation of constexpr function (note that variable is const, not constexpr)
  char c;
  std::cin >> c;
  const double run = half_of(c);
  assert(run == (c * 0.5));
}

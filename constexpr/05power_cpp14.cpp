#include <iostream>
#include <stdexcept>

constexpr
double compute_power(double base, int pow) {
  //if ((pow > 500) || (pow < -500))  throw std::range_error("abs(pow) exceeds 500");
  if (pow < 0) {  base = 1.0/base;  pow = -pow;  }

  double result = 1.0;
  for (int i = 0; i < pow; ++i)  result *= base;

  return result;
}

int main() {
  constexpr double n = compute_power(1.01, 999);
  constexpr double m = compute_power(1.01,-999);
  std::cout << n << std::endl;
  std::cout << m << std::endl;

  static_assert(// compute at compile time
    compute_power(2.0, 0) ==  1.0    , "Yipe!");
  static_assert(
    compute_power(2.0, 5) == 32.0    , "Yipe!");
  static_assert(
    compute_power(2.0,-5) ==  0.03125, "Yipe!");
}

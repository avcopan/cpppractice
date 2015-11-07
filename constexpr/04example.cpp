#include <iostream>

namespace detail {

  // implementation
  constexpr
  double pow_int_cpp11(double base, int pow) {
    return (pow == 0 ? 1.0 : base * pow_int_cpp11(base, pow - 1)); // recursive evaluation of base * base * base ... [pow times]
  }

}

// user interface
constexpr
double compute_power(double base, int pow) {
  using namespace detail;
  return  (pow > 500) || (pow < -500) ?  // implementation is recursive, so we want to limit the powonent somewhere -- max recursion depth is ~500
            throw std::range_error("abs(pow) exceeds 100")
          : pow >= 0 ?
              pow_int_cpp11(base, pow)
            : pow_int_cpp11(1.0 / base, -1. * pow); // if
}

int main() {
  constexpr double n = compute_power(1.01, 499);
  constexpr double m = compute_power(1.01,-499);
  std::cout << n << std::endl;
  std::cout << m << std::endl;
}

#include <iostream>
#include <typeinfo>

/* classic C++ typelist */

template<class H, class T>
struct typelist {
  typedef H head;
  typedef T tail;
};

int main() {
  typedef typelist<float, typelist<double, long double> > floating_point_types;
  std::cout << typeid(floating_point_types::head).name() << std::endl;
  std::cout << typeid(floating_point_types::tail).name() << std::endl;
  std::cout << typeid(floating_point_types::tail::head).name() << std::endl;
  std::cout << typeid(floating_point_types::tail::tail).name() << std::endl;
}

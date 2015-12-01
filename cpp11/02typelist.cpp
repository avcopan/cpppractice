#include <iostream>
#include <typeinfo>

/* recursive solution -- get_element_impl drops the first
   type and decrements n until it hits 0, at which point
   the first type is the one we need.  At that point, the
   specialization below gets called and returns the type. */
template <std::size_t n, typename T, typename ...Ts>
struct get_element_impl {
  using type = typename get_element_impl<n-1, Ts...>::type;
};

template <typename T, typename ...Ts>
struct get_element_impl<0, T, Ts...> {
  using type = T;
};

/* modern C++ typelist */
template<class ...Ts>
struct typelist {
  template <std::size_t n>
  using get_element = typename get_element_impl<n, Ts...>::type;
};




int main() {
  typedef typelist<float, double, long double> floating_point_types;

  std::cout << typeid(floating_point_types::get_element<0>).name() << std::endl;
  std::cout << typeid(floating_point_types::get_element<1>).name() << std::endl;
  std::cout << typeid(floating_point_types::get_element<2>).name() << std::endl;

  typedef typelist<bool,
                   char, signed char, unsigned char, char16_t, char32_t, wchar_t,
                   int, unsigned int,
                   short, unsigned short,
                   long, unsigned long, long long, unsigned long long> integral_types;

  std::cout << typeid(integral_types::get_element< 0>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 1>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 2>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 3>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 4>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 5>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 6>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 7>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 8>).name() << std::endl;
  std::cout << typeid(integral_types::get_element< 9>).name() << std::endl;
  std::cout << typeid(integral_types::get_element<10>).name() << std::endl;
  std::cout << typeid(integral_types::get_element<11>).name() << std::endl;
  std::cout << typeid(integral_types::get_element<12>).name() << std::endl;
  std::cout << typeid(integral_types::get_element<13>).name() << std::endl;
  std::cout << typeid(integral_types::get_element<14>).name() << std::endl;
}

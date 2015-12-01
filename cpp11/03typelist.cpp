#include <utility> // std::index_sequence, std::index_sequence_for
#include <typeinfo>
#include <iostream>

/* alternative solution -- requires C++14 */

template <std::size_t n, typename T>
struct indexed {
  using type = T;
};

template <typename Ns, typename ...Ts>
struct indexer;

template <std::size_t ...ns, typename ... Ts>
struct indexer <std::index_sequence<ns...>, Ts...> : indexed<ns, Ts>... {
};
// indexer<std::index_sequence<0,1,2,3>,T1,T2,T3,T4>> derives from
// indexed<0,T1>, indexed<1,T2>, indexed<2,T3>, and indexed<3,T4>

template <std::size_t n, typename T>
static indexed<n, T> select(indexed<n, T>); // note -- this is a function named "select"
// select<2>( indexer<std::index_sequence<0,1,2,3>,T1,T2,T3,T4>> )'s argument
// derives from indexed<2,T3>, so it will be type-converted to that and the return type
// becomes indexed<2,T3>.

template <std::size_t n, typename ...Ts>
using get_element_impl = typename decltype(select<n>( indexer<std::index_sequence_for<Ts...>, Ts...>() ))::type;
// decltype on the return type of select<2>(indexer<std::index_sequence<0,1,2,3>,T1,T2,T3,T4>>) yields
// indexed<2,T3>, which (see above) uses type alias ::type with value T3


/* modern C++ typelist */
template<class ...Ts>
struct typelist {
  template <std::size_t n>
  using get_element = get_element_impl<n, Ts...>;
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

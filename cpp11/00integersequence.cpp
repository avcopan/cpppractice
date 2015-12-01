#include <utility> // std::integer_sequence
#include <iostream>

/*
template <class T, T... Ints>
class integer_sequence {

  // member types
  typedef value_type T;

  // member functions
  static constexpr std::size_t size(); // equivalent to sizeof...(Ints)
};


// helper templates
template<std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

template<class T, T N>
using make_integer_sequence = integer_sequence<T, 0, 1, [...] , N-2, N-1>;

template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template<class... T>
using index_sequence_for = std::make_index_sequence<sizeof...(T)>;
*/

int main() {
  std::integer_sequence<bool,true,true,true,false,true,false,false,false> seq1;

  std::cout << seq1.size() << std::endl;

  std::make_integer_sequence<int, 9> range9;

  std::cout << range9.size() << std::endl;
}

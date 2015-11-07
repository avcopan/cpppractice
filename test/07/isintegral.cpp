#include <iostream>


template<class T> struct is_integral {
  static bool value;
};

template<class T>
bool is_integral<T>::value = false;


int main() {
  std::cout << is_integral<char>::value << std::endl;
}

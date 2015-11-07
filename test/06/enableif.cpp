#include <iostream>
#include <typeinfo> // provides typeid

template<bool B, class T=void> struct enable_if {
  typedef T type;
};


int main() {
  enable_if<true,char>::type variable;

  std::cout << typeid(variable).name() << std::endl;
}

#include <iostream>

template <class T>
struct hasSerialize {
  typedef char yes[1];
  typedef yes  no [2];

  template <typename U, U u>
  struct reallyHas;

  template <typename C>
  static yes& test(reallyHas<std::string (C::*)()      , &C::serialize>*) {}
  template <typename C>
  static yes& test(reallyHas<std::string (C::*)() const, &C::serialize>*) {} 

  template<typename>
  static no&  test(...) {}

  static const bool value = ( sizeof(test<T>(0)) == sizeof(yes) );
};



/* TRY IT OUT: */


// type A with only a to_string overload
struct A {};

std::string to_string(const A&) {
  return "I'm an A!";
}

// type B with a serialize method
struct B {
  std::string serialize() const {
    return "I'm a  B!";
  }
};

// type C with a "wrong" serialize member (not a method) and a to_string overload
struct C {
  std::string serialize;
};

std::string to_string(const C&) {
  return "I'm a  C!";
}

int main() {
  std::cout << hasSerialize<A>::value << std::endl;
  std::cout << hasSerialize<B>::value << std::endl;
  std::cout << hasSerialize<C>::value << std::endl;
}

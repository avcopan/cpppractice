#include <boost/hana.hpp>
#include <iostream>
#include <string>

namespace hana = boost::hana;

// check if a type has a serialize method
auto hasSerialize = hana::is_valid([](auto&& x) -> decltype(x.serialize()) { });

// serialize any kind of objects
template<typename T>
std::string serialize(const T& obj) {
  return hana::if_(hasSerialize(obj), [](auto& x) {return x.serialize();}, [](auto& x) {return to_string(x);})(obj);
}

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
  A a;
  B b;
  C c;

  std::cout << serialize(a) << std::endl;
  std::cout << serialize(b) << std::endl;
  std::cout << serialize(c) << std::endl;
}

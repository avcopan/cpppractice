#include <string>
#include <boost/operators.hpp>
#include <iostream>

class A : boost::totally_ordered<A>, boost::equivalent<A> { // boost::totally_ordered includes all operators used, but requires definition
    std::string name_;                                      // of both operator< and operator== -- boost::equivalent provides operator== via
  public:                                                   // operator<, so when our class derives from both we need only define one
    A() {}
    explicit A (const std::string& name) : name_(name) {}
    friend bool operator< (const A& lhs, const A& rhs) { return lhs.name_ < rhs.name_; }
};


int main()
{
  A a1("aaa");
  A a2("aab");

  std::cout << "a1 == a2: " << (a1 == a2 ? "true" : "false") << std::endl;
  std::cout << "a1 != a2: " << (a1 != a2 ? "true" : "false") << std::endl;
  std::cout << "a1 <= a2: " << (a1 <= a2 ? "true" : "false") << std::endl;
  std::cout << "a1 >= a2: " << (a1 >= a2 ? "true" : "false") << std::endl;
  std::cout << "a1 <  a2: " << (a1 <  a2 ? "true" : "false") << std::endl;
  std::cout << "a1 >  a2: " << (a1 >  a2 ? "true" : "false") << std::endl;
  std::cout << "a1 == a1: " << (a1 == a1 ? "true" : "false") << std::endl;
  std::cout << "a1 != a1: " << (a1 != a1 ? "true" : "false") << std::endl;
  std::cout << "a1 <= a1: " << (a1 <= a1 ? "true" : "false") << std::endl;
  std::cout << "a1 >= a1: " << (a1 >= a1 ? "true" : "false") << std::endl;
  std::cout << "a1 <  a1: " << (a1 <  a1 ? "true" : "false") << std::endl;
  std::cout << "a1 >  a1: " << (a1 >  a1 ? "true" : "false") << std::endl;
  std::cout << "a2 == a2: " << (a2 == a2 ? "true" : "false") << std::endl;
  std::cout << "a2 != a2: " << (a2 != a2 ? "true" : "false") << std::endl;
  std::cout << "a2 <= a2: " << (a2 <= a2 ? "true" : "false") << std::endl;
  std::cout << "a2 >= a2: " << (a2 >= a2 ? "true" : "false") << std::endl;
  std::cout << "a2 <  a2: " << (a2 <  a2 ? "true" : "false") << std::endl;
  std::cout << "a2 >  a2: " << (a2 >  a2 ? "true" : "false") << std::endl;
}

#include <boost/bind.hpp>
#include <iostream>
#include <string>

class SomeClass {
  public:
    typedef void result_type;
    void print_string(const std::string& s) const { std::cout << s << std::endl; }
};

void print_string(const std::string s) { std::cout << s << std::endl; }

int main()
{
  (boost::bind(&print_string,_1))("Hello func!"); // when calling a free function, _1 refers to the function argument

  SomeClass c;
  (boost::bind(&SomeClass::print_string,_1,_2))(c,"Hello member!"); // when calling a class method, _1 must be an instance of the class
                                                                    // which is, in a sense, an implicit argument -- like *self* in python

  // alternatively, we can creat a binder that invokes print_string on the same object every time it is invoked
  (boost::bind(&SomeClass::print_string,SomeClass(),_1))("Hello member!");
}

#include "boost/scoped_ptr.hpp"
#include <memory>
#include <string>
#include <iostream>

int main()
{
  boost::scoped_ptr<std::string> p_scoped(new std::string("Hello"));
  std::auto_ptr<std::string>     p_auto  (new std::string("Hello"));

  std::cout << p_scoped->size() << std::endl;
  std::cout << p_auto->size()   << std::endl;

//boost::scoped_ptr<std::string> p_another_scoped = p_scoped; // illegal
  std::auto_ptr<std::string>     p_another_auto   = p_auto;

  std::cout << p_another_auto->size() << std::endl;
  std::cout << p_auto->size()         << std::endl; // this causes seg fault
}

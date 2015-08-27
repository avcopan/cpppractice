#include "boost/scoped_ptr.hpp"
#include <string>
#include <iostream>

int main()
{
  boost::scoped_ptr<std::string> p(new std::string("Use scoped_ptr often."));

  if(p) std::cout << *p << std::endl;

  std::size_t i = p->size();

  *p = "Acts just like a pointer";

  if(p) std::cout << *p << std::endl;
}

#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <string>

int main()
{
  boost::tuple<int,double,std::string> triple(42, 3.14, "My first tuple!");

  std::cout << boost::tuples::get<0>(triple) << std::endl;
  std::cout << boost::tuples::get<1>(triple) << std::endl;
  std::cout << boost::tuples::get<2>(triple) << std::endl;

  std::cout << triple.get<0>() << std::endl;
  std::cout << triple.get<1>() << std::endl;
  std::cout << triple.get<2>() << std::endl;
}

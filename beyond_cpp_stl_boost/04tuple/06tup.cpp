#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <iostream>

int main()
{
  boost::tuple<int,int,int> tup1, tup2;
  std::cout << "Ender three ints as (i1 i2 i3):  " << std::endl;
  std::cin >> tup1;

  std::cout << "Enter three ints as [i1, i2, i3]:" << std::endl;
  std::cin >> boost::tuples::set_open('[') >> boost::tuples::set_close(']') >> boost::tuples::set_delimiter(',') >> tup2;

  std::cout << "Here they are:" << std::endl;
  std::cout << tup1 << std::endl;
  std::cout << boost::tuples::set_open('\"') << boost::tuples::set_close('\'') << boost::tuples::set_delimiter('_') << tup2 << std::endl;
}

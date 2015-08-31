#include <boost/tuple/tuple.hpp>
#include <boost/math/common_factor.hpp>
#include <iostream>

boost::tuple<int,int> gcd_lcm(int i1, int i2)
{
  return boost::make_tuple(boost::math::gcd(i1,i2), boost::math::lcm(i1,i2)); // boost::tuple provides a way of giving multiple return values
}

int main()
{
  // the "old" way
  boost::tuple<int,int> tup;
  tup = gcd_lcm(12,18);
  int gcd = tup.get<0>();
  int lcm = tup.get<1>();

  std::cout << "Integers 12 and 18:" << std::endl;
  std::cout << " - greatest common divisor: " << gcd << std::endl;
  std::cout << " - least common multiple:   " << lcm << std::endl;

  // the "new" way
  boost::tie(gcd, lcm) = gcd_lcm(15,20); // boost::tie takes arguments as non-const reference and "ties" them to a tuple -- i.e., we can store
                                         // the pair of return values from gcd_lcm() simultaneously
                                         // this behaves effectively like gcd, lcm = (val1, val2) in python

  std::cout << "Integers 15 and 20:" << std::endl;
  std::cout << " - greatest common divisor: " << gcd << std::endl;
  std::cout << " - least common multiple:   " << lcm << std::endl;

  // another example
  short s; double d;
  boost::tie(s, d) = std::make_pair(3,0.141592);
  std::cout << "boost::tie(s,d) = std::make_pair(3,0.141592)" << std::endl;
  std::cout << "s: " << s << std::endl;
  std::cout << "d: " << d << std::endl;

  // another example
  int i1, i2, i3, i4, i5;
  boost::tie(i1, i2, i3, i4, i5) = boost::make_tuple(1, 2, 3, 4, 5);
  std::cout << "boost::tie(i1, i2, i3, i4, i5) = boost::make_tuple(1, 2, 3, 4, 5)" << std::endl;
  std::cout << "i1: " << i1 << std::endl;
  std::cout << "i2: " << i2 << std::endl;
  std::cout << "i3: " << i3 << std::endl;
  std::cout << "i4: " << i4 << std::endl;
  std::cout << "i5: " << i5 << std::endl;
}

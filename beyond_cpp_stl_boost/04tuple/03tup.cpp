#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <iostream>
#include <string>

int main()
{
  boost::tuple<int,char,std::string> tup1(11,'a',"Match?");
  boost::tuple<short,char,std::string> tup2(11,'b',"Match?");

  std::cout << std::boolalpha; // I/O manipulator that causes bool values to be represented as "true" and "false" rather than integer values

  std::cout << "Comparison: tup1 is less than tup2" << std::endl;

  std::cout << "tup1 == tup2: " << (tup1 == tup2) << std::endl;
  std::cout << "tup1 != tup2: " << (tup1 != tup2) << std::endl;
  std::cout << "tup1 <= tup2: " << (tup1 <= tup2) << std::endl;
  std::cout << "tup1 >= tup2: " << (tup1 >= tup2) << std::endl;
  std::cout << "tup1 <  tup2: " << (tup1 <  tup2) << std::endl;
  std::cout << "tup1 >  tup2: " << (tup1 >  tup2) << std::endl;

  tup2.get<1>() = tup1.get<1>(); // in this case, equivalent to tup1 = tup2;
  
  std::cout << "Comparison: tup1 equals tup2" << std::endl;

  std::cout << "tup1 == tup2: " << (tup1 == tup2) << std::endl;
  std::cout << "tup1 != tup2: " << (tup1 != tup2) << std::endl;
  std::cout << "tup1 <= tup2: " << (tup1 <= tup2) << std::endl;
  std::cout << "tup1 >= tup2: " << (tup1 >= tup2) << std::endl;
  std::cout << "tup1 <  tup2: " << (tup1 <  tup2) << std::endl;
  std::cout << "tup1 >  tup2: " << (tup1 >  tup2) << std::endl;
}

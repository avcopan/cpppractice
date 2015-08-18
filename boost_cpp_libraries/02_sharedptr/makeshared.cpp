#include <boost/make_shared.hpp>
#include <typeinfo>
#include <iostream>

int main()
{
  auto pint1 = boost::make_shared<int>(1);
  std::cout << pint1.get()          << std::endl;
  std::cout << *pint1.get()         << std::endl;
  std::cout << typeid(pint1).name() << std::endl;

  auto pint2 = boost::make_shared<int[]>(10);
  std::cout << pint2.get()          << std::endl;
  std::cout << *pint2.get()         << std::endl;
  std::cout << typeid(pint2).name() << std::endl;

  pint2[0] = 0;
  pint2[1] = 1;
  pint2[2] = 2;
  pint2[3] = 3;
  pint2[4] = 4;
  pint2[4] = 4;
  pint2[5] = 5;
  pint2[6] = 6;
  pint2[7] = 7;
  pint2[8] = 8;
  pint2[9] = 9;
  for(int i; i<10; ++i)
    std::cout << pint2[i] << std::endl;
}

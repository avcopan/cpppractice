#include <utility>
#include <iostream>
#include <iomanip>

int main()
{
  std::pair<int,float> p = std::make_pair(5, 8.8);
  std::cout << std::setw(2) << p.first << std::setw(4) << p.second << std::endl;

  std::pair<int,int> i = p;
  std::cout << std::setw(2) << i.first << std::setw(2) << i.second << std::endl;
}

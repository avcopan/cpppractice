#include <boost/lexical_cast.hpp>
#include <vector>
#include <iostream>

int main()
{
  std::cout << boost::lexical_cast<std::string>(4987324) << std::endl;
}

#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
namespace bl = boost::lambda;

int main()
{
  typedef std::istream_iterator<int> iit;

  std::for_each(iit(std::cin), iit(), std::cout << (bl::_1 * 3) << " ");
  std::cout << std::endl;
}

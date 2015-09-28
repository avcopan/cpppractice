#include <boost/shared_ptr.hpp>
#include <iostream>

int main()
{
  boost::shared_ptr<int[]> array(new int[5]);
  array[0] = 0; array[1] = 1; array[2] = 2; array[3] = 3; array[4] = 4;
  std::cout << array[0] << ' ' << array[1] << ' ' << array[2] << ' ' << array[3] << ' ' << array[4] << std::endl;

  std::cout << *(++array) << std::endl;
}

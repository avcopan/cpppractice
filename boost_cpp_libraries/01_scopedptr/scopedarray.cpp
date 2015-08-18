#include <cstdio>
#include <boost/scoped_array.hpp>

int main()
{
  boost::scoped_array<int> arr{new int[2]};
  *arr.get() = 1;
  arr[1] = 2;
  printf("[%d %d]\n", arr[0], arr[1]);
  arr.reset(new int[3]);
}

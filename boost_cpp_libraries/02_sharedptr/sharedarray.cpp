#include <cstdio>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

int main()
{
  // shared arrays
  boost::shared_array<int> arr1{new int[2]};

  boost::shared_array<int> arr2{arr1};

  arr2[0] = 7;
  arr2[0] = 13;

  printf("%p\n", arr1.get());
  printf("%d\n", arr1[0]);
  printf("%d\n", arr1[1]);
  printf("%p\n", arr2.get());
  printf("%d\n", arr2[0]);
  printf("%d\n", arr2[1]);

  // equivalent: create a shared-pointer array
  boost::shared_ptr<int[]> pint1{new int[2]};

  pint1[0] = 8;
  pint1[1] = 14;

  printf("%p\n", pint1.get());
  printf("%d\n", *pint1.get());
  printf("%d\n", pint1[0]);
  printf("%d\n", pint1[1]);
}

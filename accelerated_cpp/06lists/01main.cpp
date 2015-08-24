#include <list>
#include "print.hpp"
#include "partition.hpp"

bool condition(int n) { return n > 0; }

int main()
{
  int numbers[] =  {1, 9, 2, -8, 3, -4, 7, 10, 11, -1, -40, 28};
  std::list<int> l(numbers, numbers + sizeof(numbers)/sizeof(numbers[0]));
  print_list(l);

  // std::list has its own optimized sort function, since this template does not support random access indexing
  l.sort();
  print_list(l);

  std::list<int> m = partition(l, condition);
  print_list(l);
  print_list(m);
}

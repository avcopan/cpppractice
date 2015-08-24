#include <iostream>
#include <vector>
#include "print.hpp"
#include "partition.hpp"

bool condition(int i) { return i > 5; }

int main()
{
  static const int numbers[] = {1, 9, 2, 8, 3, 4, 7, 10, 11, -1, -40, 28};
  std::vector<int> v(numbers, numbers + sizeof(numbers)/sizeof(numbers[0]));
  print_vec(v);

  //std::vector<int> u = partition(v, condition);
  std::vector<int> u = partition_with_iter(v, condition);
  print_vec(v);
  print_vec(u);
}

#include <vector>
#include <algorithm> // std::copy, std::remove_copy_if, std::remove_if
#include <iterator>  // std::back_inserter

#include <iostream>

#include "print.hpp"

bool nonnegative(int n) { return n >= 0; }
bool negative(int n)    { return n <  0; }

std::vector<int> partition(std::vector<int>& pass)
{
  std::vector<int> fail;
  std::remove_copy_if(pass.begin(), pass.end(), std::back_inserter(fail), nonnegative);
  pass.erase(std::remove_if(pass.begin(), pass.end(), negative), pass.end());
  return fail;
}

int main()
{
  int numbers[] =  {1, 9, 2, -8, 3, -4, 7, 10, 11, -1, -40, 28};
  std::vector<int> v;
  std::copy(numbers, numbers + 12, std::back_inserter(v));
  print_vector(v);

  std::vector<int> u = partition(v);
  print_vector(u);
  print_vector(v);
}

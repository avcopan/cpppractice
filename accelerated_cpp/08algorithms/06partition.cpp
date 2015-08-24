#include "print.hpp"
#include <vector>
#include <algorithm> // provide std::partition and std::stable_partition

bool nonnegative(int n) { return n >= 0; }

int main()
{
  int numbers[] =  {-1, -2, -3, 1, 9, 2, -8, 3, -4, 7, 10, 11, -1, -40, 28};
  std::vector<int> v;
  std::copy(numbers, numbers + 12, std::back_inserter(v));
  print_vector(v);

  std::partition(v.begin(), v.end(), nonnegative); // faster, but does not preserve order
  print_vector(v);

  std::vector<int> u;
  std::copy(numbers, numbers + 12, std::back_inserter(u));

  std::stable_partition(u.begin(), u.end(), nonnegative); // preserves order -- in this case it will behave like std::sort
  print_vector(u);
}

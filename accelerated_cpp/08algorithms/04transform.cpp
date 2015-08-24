#include <algorithm> // provides std::copy and std::transform
#include <iterator>  // provides std::back_inserter
#include <numeric>   // provides std::accumulate
#include <vector>

#include "print.hpp"

int square(int n) { return n * n; }

int main()
{
  int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> v(10);
  std::copy(numbers, numbers + 10, v.begin());

  std::vector<int> u;
  std::transform(v.begin(), v.end(), std::back_inserter(u), square);

  print_vector(v);
  print_vector(u);

  int sum          = std::accumulate(v.begin(), v.end(), 0); // like sum(range) -- 0 is starting value
  int sumofsquares = std::accumulate(u.begin(), u.end(), 0); // like sum(x*x for x in range) -- 0 is starting value
  std::cout << sum          << std::endl;
  std::cout << sumofsquares << std::endl;
}

#include <vector>
#include "print.hpp"

#include <iterator> // provides back_inserter

int main()
{
  int numbers1[] = { 1,  2,  3,  4,  5,  6,  7};
  int numbers2[] = {-1, -2, -3, -4, -5, -6, -7};

  std::vector<int> v1(7);
  std::vector<int> v2(7);

  std::copy(numbers1, numbers1 + 7, v1.begin());
  std::copy(numbers2, numbers2 + 7, v2.begin());

  print_vector(v1);
  print_vector(v2);

  v1.insert(v1.begin() + 3, v2.begin(), v2.end());

  print_vector(v1);

  std::vector<int> v3(7);
  std::vector<int> v4(7);

  std::copy(numbers1, numbers1 + 7, v3.begin());
  std::copy(numbers2, numbers2 + 7, v4.begin());

//std::copy(v3.begin(), v3.end(), v4.begin()); // valid: copies v3 into v4
//std::copy(v3.begin(), v3.end(), v4.end()); // ERROR: runs over the end without initializing new memory
  std::copy(v3.begin(), v3.end(), std::back_inserter(v4)); // back_inserter returns back-insert iterator that
                                                           // inserts new elements at the end of v4

  print_vector(v4);
}

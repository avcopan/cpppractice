#include <iostream>
#include <vector>

int sum(std::vector<int>::const_iterator& it)
{
  return 0;
}

template<typename ... Types>
inline const
int sum(std::vector<int>::const_iterator& it, int first, Types ... rest)
{
  return first * (*it) + sum(++it, rest...);
}

int main()
{
  std::vector<int> v{1,2,3,4};
  std::vector<int>::const_iterator it = v.begin();
  std::cout << sum(it, 1, 2, 3, 4) << std::endl;
}

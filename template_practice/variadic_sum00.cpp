#include <iostream>

int sum()
{
  return 0;
}

template<typename ... Types>
inline const
int sum(int first, Types ... rest)
{
  return first + sum(rest...);
}

int main()
{
  std::cout << sum(1, 2, 3, 4) << std::endl;
}

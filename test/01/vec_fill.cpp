#include <vector>
#include <iostream>

int main()
{
  std::vector<int> shape({10, 8, 11, 2, 3});
  std::vector<int> strides(5);

  int prod = 1;
  for(int i=4; i>=0; --i)
  {
    strides[i] = prod;
    prod *= shape[i];
  }

  for(std::vector<int>::iterator it = strides.begin(); it != strides.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << std::endl;
}

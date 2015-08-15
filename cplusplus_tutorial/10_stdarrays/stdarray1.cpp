#include <iostream>
#include <array>

int main()
{
  std::array<int,3> arr = {10, 20, 30};

  for(int i=0; i<arr.size(); ++i)
    ++arr[i];

  for(int a : arr)
    std::cout << a << std::endl;
}

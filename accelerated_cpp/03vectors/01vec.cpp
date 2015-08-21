#include <iostream>
#include <vector>

int main()
{
  std::vector<double> homework;
  double x;
  while(std::cin >> x) homework.push_back(x);

  for(int i = 0; i < homework.size(); ++i)
    std::cout << homework[i] << std::endl;
}

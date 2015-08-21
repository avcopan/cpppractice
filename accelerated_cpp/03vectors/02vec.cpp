#include <iostream>
#include <vector>
#include <algorithm> // supplies std::sort

int main()
{
  std::vector<double> homework;
  double x;
  while(std::cin >> x) homework.push_back(x);  // C++ std requires push_back to be no worse than N scaling

  std::sort(homework.begin(), homework.end()); // C++ std requires std::sort() to be no worse than N log(N) scaling

  for(int i = 0; i < homework.size(); ++i)
    std::cout << homework[i] << std::endl;
}

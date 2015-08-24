#include <map>
#include "print.hpp"


int main()
{
  std::map<int, int> numcounts;

  int n;
  while(std::cin >> n) ++numcounts[n]; 

  print_map(numcounts);
}

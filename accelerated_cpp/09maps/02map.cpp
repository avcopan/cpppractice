#include <map>
#include <string>
#include "print.hpp"


int main()
{
  std::map<std::string, int> numwords;

  std::string word;
  while(std::cin >> word) ++numwords[word];

  print_map(numwords);
}

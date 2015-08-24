#include "split.hpp"
#include "print.hpp"
#include <string>
#include <vector>

int main()
{
  std::string s = "   The quick brown fox jumps over the lazy dog     ";
  std::vector<std::string> v = split(s);
  print_vector(v);
}

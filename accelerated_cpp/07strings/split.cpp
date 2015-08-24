#include "split.hpp"
#include <vector>
#include <string>
#include <cctype>

std::vector<std::string> split(const std::string& s)
{
  std::vector<std::string> v;
  typedef std::string::size_type string_size;
  string_size i = 0;

  while(i != s.size())
  {
    while(i != s.size() &&  std::isspace(s[i])) ++i; // ignore leading whitespaces

    string_size j = i;
    while(j != s.size() && !std::isspace(s[j])) ++j; // find end of word

    if(i != j)
    {
      v.push_back(s.substr(i, j - i));
      i = j;
    }
  }

  return v;
}

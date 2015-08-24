#include <cctype>
#include <vector>
#include <string>
#include <algorithm> // provides std::find_if
#include "print.hpp"

bool yes_space(char c) { return  std::isspace(c); } // passing pointer to std::isspace directly will not work b/c it's overloaded
bool not_space(char c) { return !std::isspace(c); }

std::vector<std::string> split(const std::string& s)
{
  typedef std::string::const_iterator it;
  it i = s.begin();
  std::vector<std::string> v;

  while(i != s.end())
  {
    i = std::find_if(i, s.end(), not_space);
    it j = std::find_if(i, s.end(), yes_space);
    if(i != s.end())
      v.push_back(std::string(i, j)); // note that i and j are begin and end iterators on s, so std::string(i, j) returns a word
    i = j;
  }

  return v;
}

int main()
{
  std::string s = "    The   quick   brown   fox \n  jumps   over   the   lazy   dog      ";

  std::vector<std::string> v = split(s);

  print_vector(v);
}

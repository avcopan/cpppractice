#include <string>
#include <iostream>
#include <sstream>

int main()
{
//std::cout << std::to_string(355) << std::endl;// works with -std=c++11

  std::string s;
  s << "Hello world!";
  std::cout << s << std::endl;
}

#include <stdio.h>
#include <string>

std::string concatenate(const std::string& a, const std::string& b) // in order to save memory (avoid creating copies of variables
{                                                                   // you can pass const reference to your variable -- const qualifier
                                                                    // prevents the function from changing the value of the variable
  a = "Goodbye"; // this line causes a compiler error
  return a + b;
}

std::string concatenate_nonconst(std::string& a, std::string& b) // in order to save memory (avoid creating copies of variables
{
  a = "Goodbye";
  return a + b;
}

int main()
{
  std::string a = "Hello";
  std::string b = "World";
  printf("concatenate(a, b) returns %s\n", concatenate(a, b).c_str());
  printf("concatenate_nonconst(a, b) returns %s\n", concatenate_nonconst(a, b).c_str());
}

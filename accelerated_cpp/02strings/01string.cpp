#include <iostream>
#include <string>
#include "type.hpp"

int main()
{
  std::cout << "Please enter your first name: ";

  std::string name;
  std::cin >> name;

  std::cout << "Hello, " << name << "!" << std::endl;

  std::cout << type(std::cin) << std::endl;
}

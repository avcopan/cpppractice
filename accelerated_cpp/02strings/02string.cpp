#include <iostream>
#include <string>

int main()
{
  std::cout << "Enter name: ";
  std::string name;
  std::cin >> name;

  const std::string greeting = "Hello, " + name + "!";
  const std::string spaces(greeting.size(), ' ');
  const std::string stars(greeting.size(), '*');

  std::cout << std::endl;
  std::cout << "**" << stars    << "**" << std::endl;
  std::cout << "* " << spaces   << " *" << std::endl;
  std::cout << "* " << greeting << " *" << std::endl;
  std::cout << "* " << spaces   << " *" << std::endl;
  std::cout << "**" << stars    << "**" << std::endl;
}

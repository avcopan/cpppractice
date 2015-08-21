#include <iostream>
#include "type.hpp"

int main()
{
  (std::cout << "Hello, world!") << std::endl; // << is left-associative operator, std::endl is a "manipulator"
  /* this expression evaluates to std::cout, which now has the characters "Hello, world!" written to it, followed
     by the manipulator std::endl acting on it to end the current line of output.  std::cout then writes this stream
     to screen and its value gets discarded. */

//std::cout << ("Hello, world!" << std::endl); // this will break -- the manipulator std::endl can only act on std::ostream, not on a char[14]

  std::cout << type(std::cout) << " " << type("Hello, world!") << std::endl;
}

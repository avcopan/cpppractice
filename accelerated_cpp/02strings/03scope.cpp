#include <iostream>

int main()
{
  int m = 0;
//int m = 1; // this fails -- variable m has alread been initialized
  {int n = 3;} // n gets released immediately after declaring it
  {int n = 4;} // n is now in a different scope, so it can be redefined
//std::cout << n << std::endl; // this failes -- variable not declared in this scope
  {int n = 5; std::cout << n << std::endl; }
  std::cout << (16 << 2) << std::endl; // shift binary *1000* = 2^4 = 16 by 2 bits to the left, giving *100000* = 2^6 = 64
  std::cout << (16 >> 2) << std::endl; // shift binary *1000* = 2^4 = 16 by 2 bits to the right, giving *10* = 2^2 = 4
}

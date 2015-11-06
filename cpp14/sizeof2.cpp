#include <iostream>

typedef char yes;   // size: 1 byte
typedef yes  no[2]; // size: 2 bytes

// two functions using our type with a different size
yes& f1();
no&  f2();

int main() {
  std::cout << (sizeof(f1()) == sizeof(f2())) << std::endl;// output: 0
  std::cout << (sizeof(f1()) == sizeof(f1())) << std::endl;// output: 1
}

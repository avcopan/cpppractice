#include <iostream>

int globvar1 = 5;
int globvar2 = 7;

int& getglob1() { return globvar1; }
int  getglob2() { return globvar2; }


int main()
{
  getglob1() = 13; // OKAY  -- getglob1() returns a reference to globvar1, which is an lvalue -- globvar1 will be set to 13
  std::cout << globvar1 << std::endl;

/*
  getglob2() = 17; // ERROR -- getglob2() returns the value of globvar2, which is an rvalue and hence cannot serve as left operand to operator=
*/
}

// other subtle lvalues:
// for int* p, the expression *(p+5) is an lvalue

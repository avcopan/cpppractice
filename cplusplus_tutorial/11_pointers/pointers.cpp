#include <iostream>

int main()
{
  int  val1 =  5;
  int  val2 = 15;
  int* pnt1;
  int* pnt2;

  pnt1 = &val1; // pnt1 = address of val1
  pnt2 = &val2; // pnt2 = address of val2
  *pnt1 += 1;   // increment value pointed to by pnt1 by 1
  *pnt2 += 2;   // increment value pointed to by pnt2 by 2

  std::cout << val1 << std::endl;
  std::cout << val2 << std::endl;

  val1 =  5;
  val2 = 15;
  pnt1 = pnt2;  // set pnt1 to pnt2, so they now both point to the address of val2
  *pnt1 = 20;

  std::cout << val1 << std::endl;
  std::cout << val2 << std::endl;
}

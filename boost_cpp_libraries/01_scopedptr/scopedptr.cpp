#include <boost/scoped_ptr.hpp>
#include <iostream>

int main()
{
  boost::scoped_ptr<int> pint{new int{1}}; // new smart-pointer to int declared and given the value 1

  std::cout << *pint << std::endl;         // dereference smart-pointer to print its value

  std::cout << (bool(pint) ? "true" : "false") << std::endl; // cast to bool returns true if the smart-pointer is non-empty

  pint.reset(new int{2}); // reset smart-pointer with new address and new value 2

  std::cout << *pint << std::endl;         // dereference smart-pointer to print its value
  std::cout << *pint.get() << std::endl;   // .get() simply returns the pointer value, so dereferencing and printing gives the same thing

  pint.reset(); // empty reset -- now the memory has been freed and the pointer is empty

  std::cout << (bool(pint) ? "true" : "false") << std::endl; // cast to bool returns false now that the smart-pointer is empty
}

#include <memory>
#include <iostream>

int main()
{
  std::auto_ptr<int> ptr(new int); // ptr = new int; is invalid
  *ptr = 5;
  std::cout << ptr.get() << " " << *ptr << std::endl;
}

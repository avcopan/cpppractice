#include <memory>
#include <iostream>
#include <iomanip>

template <class T>
std::ostream& operator<< (std::ostream& strm, const std::auto_ptr<T>& p)
{
  if(p.get() == NULL) strm << "NULL";
  else strm << *p;
  return strm;
}

// const auto_ptr's can change value but not ownership (their address is const) -- i.e. they behave like T* const p
int main()
{
  const std::auto_ptr<int> p(new int(42));
  const std::auto_ptr<int> q(new int(0));
  const std::auto_ptr<int> r; // if I understand it right, this variable is basically permanently useless -- it will always refer to NULL

  std::cout << "after initialization: " << std::endl;
  std::cout << "p: " << std::setw(10) << p.get() << std::setw(10) << p << std::endl;
  std::cout << "q: " << std::setw(10) << q.get() << std::setw(10) << q << std::endl;
  std::cout << "r: " << std::setw(10) << r.get() << std::setw(10) << r << std::endl;

  *q = *p; // change values
//*r = *p  // illegal, since r has no memory assigned
  *p = -77;
  std::cout << "after assigning values: " << std::endl;
  std::cout << "p: " << std::setw(10) << p.get() << std::setw(10) << p << std::endl;
  std::cout << "q: " << std::setw(10) << q.get() << std::setw(10) << q << std::endl;
  std::cout << "r: " << std::setw(10) << r.get() << std::setw(10) << r << std::endl;
}

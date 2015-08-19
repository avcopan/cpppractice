#include <memory>
#include <iostream>

template <class T>
std::ostream& operator<< (std::ostream& strm, const std::auto_ptr<T>& p)
{
  if(p.get() == NULL) strm << "NULL";
  else strm << *p;
  return strm;
}

int main()
{
  std::auto_ptr<int> p(new int(42));
  std::auto_ptr<int> q;

  std::cout << "after initialization" << std::endl;
  std::cout << "p: " << p << std::endl;
  std::cout << "q: " << q << std::endl;

  q = p; // this changes ownership of the new int above from p to q, wiping out p
  std::cout << "after change of ownership" << std::endl;
  std::cout << "p: " << p << std::endl;
  std::cout << "q: " << q << std::endl;

  *q += 13;
  p = q;
  std::cout << "after reassignment and changing ownership back" << std::endl;
  std::cout << "p: " << p << std::endl;
  std::cout << "q: " << q << std::endl;
}

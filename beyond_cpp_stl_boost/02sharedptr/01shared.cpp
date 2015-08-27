#include <boost/shared_ptr.hpp>
#include <iostream>

int main()
{
  boost::shared_ptr<int> a(new int(14));
  std::cout << "*a:            " << *a            << std::endl;
  std::cout << "a.get():       " << a.get()       << std::endl;
  std::cout << "a.use_count(): " << a.use_count() << std::endl;

  boost::shared_ptr<int> b = a;
  std::cout << "*a:            " << *a            << std::endl;
  std::cout << "*b:            " << *b            << std::endl;
  std::cout << "a.get():       " << a.get()       << std::endl;
  std::cout << "b.get():       " << b.get()       << std::endl;
  std::cout << "a.use_count(): " << a.use_count() << std::endl;
  std::cout << "b.use_count(): " << b.use_count() << std::endl;

  boost::shared_ptr<int> c = b;
  std::cout << "*a:            " << *a            << std::endl;
  std::cout << "*b:            " << *b            << std::endl;
  std::cout << "*c:            " << *c            << std::endl;
  std::cout << "a.get():       " << a.get()       << std::endl;
  std::cout << "b.get():       " << b.get()       << std::endl;
  std::cout << "c.get():       " << c.get()       << std::endl;
  std::cout << "a.use_count(): " << a.use_count() << std::endl;
  std::cout << "b.use_count(): " << b.use_count() << std::endl;
  std::cout << "c.use_count(): " << c.use_count() << std::endl;

  a.reset();
  std::cout << std::endl << "After calling a.reset(): " << std::endl;
  std::cout << "a.get():       " << a.get()       << std::endl;
  std::cout << "b.get():       " << b.get()       << std::endl;
  std::cout << "c.get():       " << c.get()       << std::endl;
  std::cout << "a.use_count(): " << a.use_count() << std::endl;
  std::cout << "b.use_count(): " << b.use_count() << std::endl;
  std::cout << "c.use_count(): " << c.use_count() << std::endl;

  b.reset();
  std::cout << std::endl << "After calling b.reset(): " << std::endl;
  std::cout << "a.get():       " << a.get()       << std::endl;
  std::cout << "b.get():       " << b.get()       << std::endl;
  std::cout << "c.get():       " << c.get()       << std::endl;
  std::cout << "a.use_count(): " << a.use_count() << std::endl;
  std::cout << "b.use_count(): " << b.use_count() << std::endl;
  std::cout << "c.use_count(): " << c.use_count() << std::endl;

  c.reset();
  std::cout << std::endl << "After calling c.reset(): " << std::endl;
  std::cout << "a.get():       " << a.get()       << std::endl;
  std::cout << "b.get():       " << b.get()       << std::endl;
  std::cout << "c.get():       " << c.get()       << std::endl;
  std::cout << "a.use_count(): " << a.use_count() << std::endl;
  std::cout << "b.use_count(): " << b.use_count() << std::endl;
  std::cout << "c.use_count(): " << c.use_count() << std::endl;
}

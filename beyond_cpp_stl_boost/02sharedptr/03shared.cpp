#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>

/* abstract base class */
class A {
  public:
    virtual void sing() = 0;
  protected:
    virtual ~A() {};
};

class B {
  public:
    virtual void sing() { std::cout << "Do re mi fa so la ti" << std::endl; }
};

boost::shared_ptr<B> createB() {
  boost::shared_ptr<B> p(new B());
  return p;
}


int main()
{
  std::vector<boost::shared_ptr<B> > v;
  for(int i = 0; i < 10; ++i) v.push_back(createB());

  std::cout << "The choir is gathered:" << std::endl;
  for(std::vector<boost::shared_ptr<B> >::iterator it = v.begin(); it != v.end(); ++it)
    (*it)->sing(); // equivalent to (*(*it)).sing() -- first dereference the iterator to get vector element, then dereference vector element, which is a shared_ptr
}

#include <boost/shared_ptr.hpp>
#include <cassert>
#include <iostream>

/* note: if no_ were a regular pointer attribute of classes A and B, it would be virtually
         impossible for their destructors to determine whether or not the pointers could
         be deleted in this scenario */

class A {
    boost::shared_ptr<int> no_;
  public:
    A(boost::shared_ptr<int> no) : no_(no) {}
    void value(int i) { *no_ = i; }
};

class B {
    boost::shared_ptr<int> no_;
  public:
    B(boost::shared_ptr<int> no) : no_(no) {}
    int value() const { return *no_; }
};


int main()
{
  boost::shared_ptr<int> tmp(new int(14));
  A a(tmp);
  B b(tmp);
  a.value(28);
  assert(b.value() == 28);

  std::cout << "b.value():       " << b.value()       << std::endl; // note that .value() is not a shared_ptr method -- it's a class B method
  std::cout << "*tmp:            " << *tmp            << std::endl;
  std::cout << "tmp.use_count(): " << tmp.use_count() << std::endl;
  std::cout << "tmp.get():       " << tmp.get()       << std::endl;
}

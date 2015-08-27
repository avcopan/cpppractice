#include <boost/scoped_ptr.hpp>
#include <iostream>

struct Shoe { ~Shoe() { std::cout << "Buckle my shoe\n"; } };

class MyClass {
    boost::scoped_ptr<int> ptr;
  public:
    MyClass() : ptr(new int) { *ptr = 0; }
    int add_one() { return ++*ptr; }
};

int main()
{
  boost::scoped_ptr<Shoe> shoe(new Shoe);
  MyClass my_instance;
  std::cout << my_instance.add_one() << std::endl;
  std::cout << my_instance.add_one() << std::endl;
}

#include <boost/scoped_ptr.hpp>
#include <memory>  // std::auto_ptr

int main()
{
  {
    std::auto_ptr<int> a(new int(3));
    std::auto_ptr<int> b(new int(4));
    std::cout << "After initialization:" << std::endl;
    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
    a = b; // transfer of owner ship -- now *a is 4 and a has b's old
    std::cout << "After transfer of ownership:" << std::endl;
    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
  }
  {
    boost::scoped_ptr<int> a(new int(3));
    boost::scoped_ptr<int> b(new int(4));
    std::cout << "After initialization:" << std::endl;
    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
  //a = b; // boost::scoped_ptr does not allow transfer
  // instead, one can do:
    boost::swap(a, b);
    b.reset();
    std::cout << "After swap and reset:" << std::endl;
    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
  }
}

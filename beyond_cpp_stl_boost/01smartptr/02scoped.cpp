#include <boost/scoped_ptr.hpp>
#include <memory>  // std::auto_ptr

int main()
{
  {
    std::auto_ptr<int> a(new int(3));
    std::auto_ptr<int> b(new int(4));
    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
    a = b; // transfer of owner ship -- now *a is 4 and a has b's old
  }
  {
    boost::scoped_ptr<int> a(new int(3));
    boost::scoped_ptr<int> b(new int(4));
    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
  //a = b; // boost::scoped_ptr does not allow transfer
  }
}

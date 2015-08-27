#include <iostream>
#include <boost/operators.hpp>

class A : boost::equivalent<A> {
    int value_;
  public:
    A(int value) : value_(value) {}
    bool less_than(const A& other) const { return value_ < other.value_; }
};

bool operator< (const A& lhs, const A& rhs) { return lhs.less_than(rhs); }

int main()
{
  A a1(11);
  A a2(12);

  std::cout << "a1 == a2: " << (a1 == a2 ? "true" : "false") << std::endl;
  std::cout << "a1 <  a2: " << (a1 <  a2 ? "true" : "false") << std::endl;
}

#include <vector>
#include <iostream>
#include <iterator> // provides std::ostream_iterator<T>

template <typename R, typename T, typename Arg>
class BoundType {
  private:
    typedef R (T::*fn)(Arg); // somehow, magically, this is declaring the type of fn
    fn fn_;
    T t_;
  public:
    BoundType(fn f, const T& t) : fn_(f), t_(t) {} 
    R operator() (Arg& a) { return (t_.*fn_)(a); } // call to BoundType<R,T,Arg>( argument ) returns dereferenced fn acting on ( argument )
};

namespace {
  class Placeholder {}; // declares empty Placeholder class
  Placeholder _1;       // declares _1 as object of Placeholder class
}

// R is return type, T is class type (of which fn is a method), and Arg is argument type
// so from R (T::*fn)(Arg), R is deduced as fn return type, T as fn's class, and Arg as fn's argument type
template <typename R, typename T, typename Arg>
BoundType<R,T,Arg> simple_bind(R (T::*fn)(Arg), const T& t, const Placeholder&)
{
  return BoundType<R,T,Arg>(fn, t);
}


/* Now, let's test it! */

class Test {
  public:
    void do_stuff(const std::vector<int>& v) { std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout,"\n")); }
};

int main()
{
  Test t;
  std::vector<int> v;
  v.push_back(42);
  v.push_back(21);
  v.push_back(9);

  simple_bind(&Test::do_stuff, t, _1)(v);
}

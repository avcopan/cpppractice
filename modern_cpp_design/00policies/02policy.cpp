#include <iostream>

template<typename ReductionPolicy>
class Foo : private ReductionPolicy {
  private:
    using ReductionPolicy::reduce;
    int _value;
  public:
    // constructors
    Foo() : _value(0) {}
    Foo(int value) : _value(value) {}
    // methods
    void apply_reduction() {reduce(_value);}
    void print()           {std::cout << _value << std::endl;}
};

namespace Policy {
  namespace Reduction {

    class Decrement {
      protected:
        void reduce(int& value) {value--;}
    };

    class Half {
      protected:
        void reduce(int& value) {value /= 2;}
    };

    class Zero {
      protected:
        void reduce(int& value) {value = 0;}
    };

  }
}

int main() {
  Foo< Policy::Reduction::Decrement > f1(42);
  Foo< Policy::Reduction::Half      > f2(42);
  Foo< Policy::Reduction::Zero      > f3(42);

  f1.print();
  f1.apply_reduction();
  f1.print();

  f2.print();
  f2.apply_reduction();
  f2.print();

  f3.print();
  f3.apply_reduction();
  f3.print();
}

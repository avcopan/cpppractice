#include <iostream>
#include <typeinfo>

/*
  The compiler will try this overload since it's less generic than the
  variadic one.  T will be replaced by 'int' which gives us
    void f<int>(const int& t, int::iterator* it = nullptr);
  'int' doesn't have an iterator sub-type, but the compiler doesn't
  throw a bunch of errors.  It simply tries the next overload.
*/
template<typename T>
void f(const T& t, typename T::iterator* it = nullptr) {
  std::cout << "void f<T>(const T& t, T::iterator* it);" << " where T is " << typeid(t).name() << std::endl;
}

void f(...) {
  std::cout << "void f(...);" << std::endl;
}

int main() {
  f(1);// tries f<int>(const int&, int::iterator*) first but then passes to f(...) since int::iterator doesn't exist
       // this "substitution failure" is not treated as an error -- rather, the compiler just keeps checking overloads
       // until one works.
}

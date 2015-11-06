#include <iostream>

void f(...) {
  std::cout << "void f(...);" << std::endl;
}

template<typename T>
void f(T t) {
  t.hahahaICrash(); // now the substitution failure occurs within the function body -- this
                    // time the compiler throws an error without ever reaching f(...)
}

int main() {
  f(1);
}

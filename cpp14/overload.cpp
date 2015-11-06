#include <string>
#include <iostream>

void f(std::string s) {
  std::cout << "void f(std::string s);"   << std::endl;
}                                         
                                          
void f(double d) {                        
  std::cout << "void f(double d);"        << std::endl;
}                                         
                                          
void f(int i) {                           
  std::cout << "void f(int i);"           << std::endl;
}                                         
                                          
void f(...) {                             
  std::cout << "void f(...);"             << std::endl;
}

template<typename... Ts>
void f(Ts... ts) {
  std::cout << "void f<Ts...>(Ts... ts);" << std::endl;
}


int main() {
  f(1); // calls f(int) if available, else f(double), else f(...)
}

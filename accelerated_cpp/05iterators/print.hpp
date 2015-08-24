#ifndef GUARD_print_hpp
#define GUARD_print_hpp
#include <vector>
#include <iostream>

template<class T>
void print_vec(std::vector<T> v)
{
  for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
    std::cout << *i << ' ';
  std::cout << std::endl;
}
#endif

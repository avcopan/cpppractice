#ifndef GUARD_print_hpp
#define GUARD_print_hpp
#include <vector>
#include <iostream>

template<class T>
void print_vector(const std::vector<T>& l)
{
  for(typename std::vector<T>::const_iterator it = l.begin(); it != l.end(); ++it)
    std::cout << *it << ' ';
  std::cout << std::endl;
}

#endif

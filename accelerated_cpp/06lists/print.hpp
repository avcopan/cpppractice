#ifndef GUARD_print_hpp
#define GUARD_print_hpp
#include <list>
#include <iostream>

template<class T>
void print_list(const std::list<T>& l)
{
  for(typename std::list<T>::const_iterator it = l.begin(); it != l.end(); ++it)
    std::cout << *it << ' ';
  std::cout << std::endl;
}

#endif

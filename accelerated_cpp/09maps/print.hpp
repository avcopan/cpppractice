#ifndef GUARD_print_hpp
#define GUARD_print_hpp_
#include <vector>
#include <list>
#include <map>
#include <iostream>

template<class T>
void print_vector(const std::vector<T>& l)
{
  for(typename std::vector<T>::const_iterator it = l.begin(); it != l.end(); ++it)
    std::cout << *it << ' ';
  std::cout << std::endl;
}

template<class T>
void print_list(const std::list<T>& l)
{
  for(typename std::list<T>::const_iterator it = l.begin(); it != l.end(); ++it)
    std::cout << *it << ' ';
  std::cout << std::endl;
}

template<class T, class U>
void print_map(const std::map<T,U>& m)
{
  for(typename std::map<T,U>::const_iterator it = m.begin(); it != m.end(); ++it)
    std::cout << it->first << ":" << it->second << ' ';
  std::cout << std::endl;
}

#endif

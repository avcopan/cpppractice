#ifndef GUARD_partition_hpp
#define GUARD_partition_hpp
#include <list>

template<class T>
std::list<T> partition(std::list<T>& l, bool (*condition)(T))
{
  std::list<T>& pass = l;
  std::list<T>  fail;
  typename std::list<T>::iterator it = l.begin();

  while(it != l.end())
  {
    if(condition(*it))
    {
      fail.push_back(*it);
      it = pass.erase(it);
    }
    else { ++it; }
  }

  return fail;
}

#endif

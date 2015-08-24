#ifndef GUARD_partition_hpp
#define GUARD_partition_hpp
#include <vector>

template<class T>
std::vector<T> partition(std::vector<T>& v, bool (*condition)(T))
{
  std::vector<T>& pass = v;
  std::vector<T>  fail;
  typename std::vector<T>::size_type i = 0;

  while(i != v.size())
  {
    if(condition(v[i]))
    {
      fail.push_back(v[i]);
      pass.erase(v.begin() + i);
    }
    else { ++i; }
  }

  return fail;
}

template<class T>
std::vector<T> partition_with_iter(std::vector<T>& v, bool (*condition)(T))
{
  std::vector<T>& pass = v;
  std::vector<T>  fail;
  typename std::vector<T>::iterator it = v.begin();

  while(it != v.end())
  {
    if(condition(*it))
    {
      fail.push_back(*it);
      it = v.erase(it);
    }
    else { ++it; }
  }

  return fail;
}
#endif

#include <vector>
#include <iostream>

template<class T>
void print_vec(const std::vector<T>& vec)
{
  for(typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it) // note: for templates, C++ requires you to qualify with *typename*
    std::cout << *it << ' ';                                                           // also, note that since we passed a const vector we have to use const_iterator
  std::cout << std::endl;
}

int main()
{
  std::vector<int> vec;
  for(int i=1; i<10; ++i) vec.push_back(i);
  print_vec<int>(vec);
}

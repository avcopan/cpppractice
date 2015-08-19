#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

// STL compliant reverse algorithm
template<class T>
void reverse_array_stl_compliant(T begin, T end)
{
  while((begin != end) && (begin != --end))
  {
    std::iter_swap(begin, end);
    ++begin;
  }
}

template<class T>
void print_vec(std::vector<T>& vec)
{
  std::cout << "[";
  for(typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it) // note: for templates, C++ requires you to qualify with *typename*
    std::cout << std::setw(3) << *it;
  std::cout << "]\n";
}

int main()
{
  std::vector<int> vec1, vec2;

  for(int i=1; i<10; ++i) vec1.push_back(i);
  for(int i=1; i<10; ++i) vec2.push_back(i);

  print_vec(vec1);
  print_vec(vec2);

  reverse_array_stl_compliant(vec1.begin(), vec1.end());
  std::reverse(vec2.begin(), vec2.end());

  print_vec(vec1);
  print_vec(vec2);
}

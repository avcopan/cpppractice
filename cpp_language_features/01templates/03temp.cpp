#include <vector>
#include <iostream>

// example of the use of default template arguments
template<class T, class container = std::vector<T> >
void print_vec(const container& vec)
{
  for(typename container::const_iterator it = vec.begin(); it != vec.end(); ++it)
    std::cout << *it << ' ';
  std::cout << std::endl;
}

int main()
{
  std::vector<int> vec;
  for(int i=1; i<10; ++i) vec.push_back(i);
  print_vec<int>(vec);
}

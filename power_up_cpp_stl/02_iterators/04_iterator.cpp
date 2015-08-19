#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

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
  std::vector<int> vec1;
  for(int i=1; i<10; ++i) vec1.push_back(i);
  print_vec(vec1);

  std::vector<int> vec2(vec1);
  std::vector<int> vec3(vec1.rbegin() + vec1.size()/2, vec1.rend());
  print_vec(vec2);
  print_vec(vec3);

  std::vector<int> vec4(vec1.begin(), vec1.begin() + vec1.size()/2);
  print_vec(vec4);

  int data[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
  std::reverse(data+2, data+7);
  std::vector<int> vec5(data, data + 11);
  print_vec(vec5);
}

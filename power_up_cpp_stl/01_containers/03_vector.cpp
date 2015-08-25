#include <vector>
#include <cstdio>

void print_vec(const std::vector<int>& vec)
{
  printf("[");
  for(auto i = vec.begin(); i != vec.end(); ++i) printf(" %3d ", *i); // auto requires C++11
  printf("]\n");
}

int main()
{
  std::vector<int> v(20);
  for(int i = 0; i < 20; ++i) v[i] = i + 1;
  print_vec(v);

  v.resize(25);
  print_vec(v);

  for(int i = 20; i < 25; ++i) v[i] = i * 2;
  print_vec(v);

  v.resize(5);
  print_vec(v);

  v.clear();
  print_vec(v);

  v.resize(15);
  print_vec(v);
}

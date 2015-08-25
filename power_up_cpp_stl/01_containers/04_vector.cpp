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
  std::vector<int> v1(20);
  for(int i = 0; i < 20; ++i) v1[i] = i + 1;
  print_vec(v1);

  std::vector<int> v2 = v1;
  print_vec(v1);
  print_vec(v2);

  std::vector<int> v3(v1); // this is equivalent to v3 = v1

  for(int i = 0; i < 20; ++i) v2[i] = 20 - i;
  for(int i = 0; i < 20; ++i) v3[i] = 20 + i;
  print_vec(v1);
  print_vec(v2);
  print_vec(v3);
}

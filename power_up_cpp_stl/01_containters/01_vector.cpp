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
  std::vector<int> v(10); // note: std::vector<int> v[10] would be incorrect -- this would be an array of 10 empty std::vector<int>s
  print_vec(v);

  for(int i = 0; i < 10; ++i) v[i]  = (i+1)*(i+1);
  print_vec(v);

  for(int i = 9; i >  0; --i) v[i] -= v[i-1];
  print_vec(v);
}

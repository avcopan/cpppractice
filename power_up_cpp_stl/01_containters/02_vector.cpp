#include <vector>
#include <cstdio>

int main()
{
  std::vector<int> v;
  printf("v.empty(): %s\n", v.empty() ? "true" : "false");
  printf("v.size():  %d\n", int(v.size()));

  for(int i = 1; i < 1000000; i *= 2) v.push_back(i);
  printf("v.empty(): %s\n", v.empty() ? "true" : "false");
  printf("v.size():  %d\n", int(v.size()));
}

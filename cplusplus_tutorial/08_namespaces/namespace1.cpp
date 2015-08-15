#include <stdio.h>

namespace foo
{
  int value() { return 5; }
}

namespace bar
{
  const double pi = 3.1416;
  double value() { return 2 * pi; }
}


int main()
{
  printf("%f\n", bar::pi     );
  printf("%d\n", foo::value());
  printf("%f\n", bar::value());
}

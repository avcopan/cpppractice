#include <stdio.h>
#include <string>

template <class T> T add(T x, T y) // take variables of any type and return the value of the binary operator + for them
{
  T xplusy;
  xplusy = x + y;
  return xplusy;
}

int main()
{
  printf("add(1,2) returns %d\n", add(1,2));
  printf("add(1.3,2.98) returns %f\n", add(1.3,2.98));
  printf("add(true,false) returns %s\n", add(true,false)?"true":"false");
  std::string a = "Hello";
  std::string b = "World";
  printf("add(\"Hello\",\"World\") [as std::strings] returns %s\n", add(a,b).c_str());

  // same code, but now illustrating the explicit instantiations
  printf("add<int>(1,2) returns %d\n", add<int>(1,2));
  printf("add<float>(1.3,2.98) returns %f\n", add<float>(1.3,2.98));
  printf("add<bool>(true,false) returns %s\n", add<bool>(true,false)?"true":"false");
  printf("add<std::string>(\"Hello\",\"World\") [as std::strings] returns %s\n", add<std::string>("Hello","World").c_str());
  // note that this last line will fail without explicit instantation <std::string>, because the arguments "Hello" and "World"
  // will be assumed to have type char* rather than std::string
}

#include <cstdio>
#include <iostream>
#include <boost/shared_ptr.hpp>

int main()
{
  {
    std::FILE* f = std::fopen("test.txt", "r");
    boost::shared_ptr<FILE> fptr(f, &std::fclose); // if we don't need to print, there's no reason to create a function wrapper
    std::fseek(fptr.get(), 42, SEEK_SET);
  } // std::fclose(FILE*) is called as the file goes out of scope

  std::cout << "By now, the FILE has been closed!" << std::endl;
}

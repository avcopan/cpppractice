#include <cstdio>
#include <iostream>
#include <boost/shared_ptr.hpp>

void deleter(FILE* file)
{
  std::cout << "The FileCloser has been called with a FILE*, which will now be closed" << std::endl;
  if (file != 0) std::fclose(file);
}


int main()
{
  {
    std::FILE* f = std::fopen("test.txt", "r");
    boost::shared_ptr<FILE> fptr(f, deleter);
    std::fseek(fptr.get(), 42, SEEK_SET); // note -- this will cause a seg fault if test.txt is an empty file
  } // deleter(FILE*) is called as the file goes out of scope

  std::cout << "By now, the FILE has been closed!" << std::endl;
}

#include <vector>
#include <iostream>
#include <iomanip>

template<typename T>
void print(const T& iterable)
{
  for(auto it = iterable.begin(); it != iterable.end(); ++it)
    std::cout << std::setw(3) << *it;
  std::cout << std::endl;
}

class Dummy {
  private:
    int d1=5, d2=5;
    std::vector<int> _stride{d1*d2*1, d2*1, 1};
  public:
    Dummy() {print(_stride);}
};

template<
class Get {
  private:
    int 
};

int main()
{
  Dummy dummy;
}

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

template<typename dtype>
class Dummy {
  private:
    std::vector<dtype> _v;
  public:
    template<typename ...V>
    Dummy(V ...v) : _v({v...}) {print(_v);}
};

int main()
{
  Dummy<int> dummy1(1,2,3,4);
  Dummy<int> dummy2(5,1,2,3,5,10,25,3);
}

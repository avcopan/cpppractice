#include <iostream>

template <class Cl>
class Pair {
    Cl pair[2];
  public:
    Pair(Cl first, Cl second){ pair[0] = first; pair[1] = second; }
    Cl get(int i) { return pair[i]; }
    Cl getmax();
    Cl getmin();
};

template <class Cl>
Cl Pair<Cl>::getmax()
{
  return pair[0] > pair[1] ? pair[0] : pair[1];
}

template <class Cl>
Cl Pair<Cl>::getmin()
{
  return pair[0] < pair[1] ? pair[0] : pair[1];
}

int main()
{
  Pair<int>       intpair(  1,  2);
  Pair<char>     charpair('a','b');
  Pair<double> doublepair(0.1,0.2);
  std::cout <<    intpair.get(0) << " " <<    intpair.get(1) << std::endl;
  std::cout <<   charpair.get(0) << " " <<   charpair.get(1) << std::endl;
  std::cout << doublepair.get(0) << " " << doublepair.get(1) << std::endl;
  std::cout <<    intpair.getmax() << std::endl;
  std::cout <<   charpair.getmax() << std::endl;
  std::cout << doublepair.getmax() << std::endl;
  std::cout <<    intpair.getmin() << std::endl;
  std::cout <<   charpair.getmin() << std::endl;
  std::cout << doublepair.getmin() << std::endl;
}

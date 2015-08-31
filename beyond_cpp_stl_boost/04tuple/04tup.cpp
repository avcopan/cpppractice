#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <iostream>
#include <vector> // apparently this provides std::sort as well?

template <int Index> class ElementLess {
  public:
    template <typename Tuple>
    bool operator() (const Tuple& lhs, const Tuple& rhs) const { return boost::get<Index>(lhs) < boost::get<Index>(rhs); }
};

int main()
{
  typedef boost::tuple<short,int,long,float,double,long double> num_tup;

  std::vector<num_tup> v;

  v.push_back(num_tup(6, 2));
  v.push_back(num_tup(7, 1));
  v.push_back(num_tup(5));

  std::sort(v.begin(), v.end(), ElementLess<1>()); // compare based on second element

  std::cout << "After sorting on second element: " << std::endl;
  std::cout << v[0].get<0>() << std::endl;
  std::cout << v[1].get<0>() << std::endl;
  std::cout << v[2].get<0>() << std::endl;

  std::sort(v.begin(), v.end(), ElementLess<0>()); // compare based on second element

  std::cout << "After sorting on first element: " << std::endl;
  std::cout << v[0].get<0>() << std::endl;
  std::cout << v[1].get<0>() << std::endl;
  std::cout << v[2].get<0>() << std::endl;
}

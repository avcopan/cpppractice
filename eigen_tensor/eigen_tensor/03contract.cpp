#include <iostream>
#include <array>
#include <Eigen/CXX11/Tensor>

int main() {
  Eigen::Tensor<double, 4> g(7,2,2,7);
  Eigen::Tensor<double, 4> t(2,2,7,7);
  g.setRandom();
  t.setRandom();

  typedef Eigen::IndexPair<int> pair;
  std::array<pair, 2> ax_pairs({pair(0,3), pair(3,2)});

  // v_ijkl = g_bija * t_klab
  Eigen::Tensor<double, 4> v = g.contract(t, ax_pairs);

  std::cout << v << std::endl;
}

#include <iostream>
#include <array>
#include "Eigen/Tensor.h"

int main() {
  Eigen::Tensor<float, 3> a(2,3,4);

  for(int i=0; i<2; ++i)
    for(int j=0; j<3; ++j)
      for(int k=0; k<4; ++k)
        a(i,j,k) = 3*4*i + 4*j + k;

  std::array<int,3> perm1{{1,2,0}};
  std::array<int,3> perm2{{2,0,1}};
  std::array<int,3> perm3{{1,0,2}};
  Eigen::Tensor<float, 3> b = a.shuffle(perm1);
  Eigen::Tensor<float, 3> c = a.shuffle(perm2);
  Eigen::Tensor<float, 3> d = a.shuffle(perm3);

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  std::cout << d << std::endl;

}

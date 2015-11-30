#include <iostream>
#include <array>
#include <Eigen/CXX11/Tensor>

int main() {
  Eigen::Tensor<float, 3> a(2,3,4);

  for(int i=0; i<2; ++i)
    for(int j=0; j<3; ++j)
      for(int k=0; k<4; ++k)
        a(i,j,k) = i + 2*j + 2*3*k;

  std::array<int,3> perm1{{1,2,0}};
  std::array<int,3> perm2{{2,0,1}};
  std::array<int,3> perm3{{1,0,2}};
  Eigen::Tensor<float, 3> b = a.shuffle(perm1);
  Eigen::Tensor<float, 3> c = a.shuffle(perm2);
  Eigen::Tensor<float, 3> d = a.shuffle(perm3);

  std::cout << a << '\n' << std::endl;
  std::cout << b << '\n' << std::endl;
  std::cout << c << '\n' << std::endl;
  std::cout << d << '\n' << std::endl;
}

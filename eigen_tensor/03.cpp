#include <iostream>
#include <Eigen/CXX11/Tensor>

// DEFAULT FORMAT IS Eigen::ColumnMajor -- in general, that should be used instead of Eigen::RowMajor

int main() {
  Eigen::Tensor<double, 4, Eigen::RowMajor> T(3,3,3,3);
  T.setZero();

  for(int i=0; i<3; ++i)
    for(int j=0; j<3; ++j)
      for(int k=0; k<3; ++k)
        for(int l=0; l<3; ++l)
          T(i,j,k,l) = 3*3*3*i + 3*3*j + 3*k + l;

  std::cout << T << std::endl;


  Eigen::Tensor<double, 4, Eigen::RowMajor> S(3,3,3,3);
  S.setZero();

  // for some reason, scalar multiplication is only allowed with scalars on the left
  S = T - T*2.0;

  std::cout << S << std::endl;
}

#include <iostream>
#include <Eigen/CXX11/Tensor>

int main() {
  Eigen::Tensor<double, 4> A(2,2,2,2);
  Eigen::Tensor<double, 4> B(2,2,2,2);
  Eigen::Tensor<double, 4> C(2,2,2,2);
  Eigen::Tensor<double, 4> D(2,2,2,2);

  for(int i=0; i<2; ++i)
    for(int j=0; j<2; ++j)
      for(int k=0; k<2; ++k)
        for(int l=0; l<2; ++l) {
          A(i,j,k,l) =    i  + 2*   j  + 2*2*   k  + 2*2*2*   l ;
          B(i,j,k,l) = (2-i) + 2*(2-j) + 2*2*(2-k) + 2*2*2*(2-l);
          C(i,j,k,l) =    i  +      j  +        k  +          l ;
          D(i,j,k,l) = 1;
        }


  Eigen::Tensor<double, 4> T1 = A + B;
  Eigen::Tensor<double, 4> T2 = A * B / (C + D);
  Eigen::Tensor<double, 4> T3 = (A + D) / (A + D * 20.0);
  Eigen::Tensor<double, 4> T4 = (A - B * 2.0 + C - D) / (A / 5.0 + B * 10.0 - C * 0.2 + D);

  std::cout << T1 << std::endl;
  std::cout << T2 << std::endl;
  std::cout << T3 << std::endl;
  std::cout << T4 << std::endl;

}

#include <iostream>
#include <Eigen/CXX11/Tensor>

int main() {
  Eigen::Tensor<int, 3> epsilon(3,3,3);
  epsilon.setZero();
  epsilon(0,1,2) =  1;
  epsilon(1,2,0) =  1;
  epsilon(2,0,1) =  1;
  epsilon(1,0,2) = -1;
  epsilon(2,1,0) = -1;
  epsilon(0,2,1) = -1;

  std::cout << epsilon << std::endl;
}

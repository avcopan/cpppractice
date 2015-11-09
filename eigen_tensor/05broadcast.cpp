#include <iostream>
#include <array>
#include "Eigen/Tensor.h"

int main() {
  Eigen::Tensor<float, 1> a(5); a.setValues({ 1.f, 2.f, 3.f, 4.f, 5.f});
  Eigen::Tensor<float, 1> b(5); b.setValues({-1.f,-2.f,-3.f,-4.f,-5.f});
  std::array<int, 2>  shape1{{1,5}}, shape2{{5,1}};
  std::array<int, 2>  bcast1{{5,1}}, bcast2{{1,5}};
  Eigen::Tensor<float, 2> c = a.reshape(shape1).broadcast(bcast1);
  Eigen::Tensor<float, 2> d = b.reshape(shape2).broadcast(bcast2);

  Eigen::Tensor<float, 2> e = a.reshape(shape1).broadcast(bcast1) + b.reshape(shape2).broadcast(bcast2);

  std::cout << a << std::endl;

  std::cout << c << std::endl;
  std::cout << d << std::endl;
  std::cout << e << std::endl;
}

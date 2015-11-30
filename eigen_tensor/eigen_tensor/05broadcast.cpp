#include <iostream>
#include <array>
#include <Eigen/CXX11/Tensor>

int main() {
  Eigen::Tensor<double, 1> a(5); a.setValues({ 1., 2., 3., 4., 5.});
  Eigen::Tensor<double, 1> b(5); b.setValues({-1.,-2.,-3.,-4.,-5.});
  std::array<int, 2> shape1({1,5}), shape2({5,1});

  Eigen::Tensor<double, 2> c = a.reshape(shape1).broadcast(shape2);
  Eigen::Tensor<double, 2> d = b.reshape(shape2).broadcast(shape1);
  Eigen::Tensor<double, 2> e = c + d;

  std::cout << a << '\n' << std::endl;
  std::cout << b << '\n' << std::endl;
  std::cout << c << '\n' << std::endl;
  std::cout << d << '\n' << std::endl;
  std::cout << e << '\n' << std::endl;
}

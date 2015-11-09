#include <iostream>
#include <array>
#include "Eigen/Tensor.h"

int main() {
  Eigen::Tensor<float, 3> a(2,3,4);
  a.setZero();

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


  Eigen::Tensor<float, 3> e = a - a*2.f;
  std::cout << e << std::endl;


  //CONTRACT

  // Create 2 matrices using tensors of rank 2
  Eigen::Tensor<double, 2> A(2, 3);
  A.setValues({{1, 2, 3}, {6, 5, 4}});
  Eigen::Tensor<double, 2> B(3, 2);
  B.setValues({{1, 2}, {4, 5}, {5, 6}});

  std::cout << A << std::endl;
  std::cout << B << std::endl;

  // Compute the traditional matrix product
  std::array<Eigen::IndexPair<int>, 1> ctr1 = { Eigen::IndexPair<int>(1, 0) };
  Eigen::Tensor<double, 2> C = A.contract(B, ctr1);

  std::cout << C << std::endl;

  A.setRandom();
  B.setRandom();

  // Compute the product of the transpose of the matrices
  std::array<Eigen::IndexPair<int>, 1> ctr2 = { Eigen::IndexPair<int>(0, 1) };
  Eigen::Tensor<double, 2> D = A.contract(B, ctr2);

  std::cout << D << std::endl;



  //BROADCAST

  Eigen::Tensor<float, 1> v(5); v.setValues({ 1.f, 2.f, 3.f, 4.f, 5.f});
  Eigen::Tensor<float, 1> u(5); u.setValues({-1.f,-2.f,-3.f,-4.f,-5.f});
  std::array<int, 2>  shape1{{1,5}}, shape2{{5,1}};
  std::array<int, 2>  bcast1{{5,1}}, bcast2{{1,5}};
  Eigen::Tensor<float, 2> V = v.reshape(shape1).broadcast(bcast1);
  Eigen::Tensor<float, 2> U = u.reshape(shape2).broadcast(bcast2);

  Eigen::Tensor<float, 2> M = v.reshape(shape1).broadcast(bcast1) + u.reshape(shape2).broadcast(bcast2);

  std::cout << v << std::endl;
  std::cout << u << std::endl;

  std::cout << V << std::endl;
  std::cout << U << std::endl;
  std::cout << M << std::endl;

}

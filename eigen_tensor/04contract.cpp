#include <iostream>
#include <array>
#include "Eigen/Tensor.h"

int main() {
    // Create 2 matrices using tensors of rank 2
    Eigen::Tensor<int, 2> a(2, 3);
    a.setRandom();
    Eigen::Tensor<int, 2> b(3, 2);
    b.setRandom();

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    // Compute the traditional matrix product
    std::array<Eigen::IndexPair<int>, 1> product_dims = { Eigen::IndexPair<int>(1, 0) };
    Eigen::Tensor<int, 2> AB = a.contract(b, product_dims);

    std::cout << AB << std::endl;
}

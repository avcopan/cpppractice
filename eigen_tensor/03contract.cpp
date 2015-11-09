#include <iostream>
#include <array>
#include "Eigen/Tensor.h"

int main() {
    // Create 2 matrices using tensors of rank 2
    Eigen::Tensor<int, 2> a(2, 3);
    a.setValues({{1, 2, 3}, {6, 5, 4}});
    Eigen::Tensor<int, 2> b(3, 2);
    b.setValues({{1, 2}, {4, 5}, {5, 6}});

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    // Compute the traditional matrix product
    std::array<Eigen::IndexPair<int>, 1> product_dims = { Eigen::IndexPair<int>(1, 0) };
    Eigen::Tensor<int, 2> AB = a.contract(b, product_dims);

    std::cout << AB << std::endl;

    // Compute the product of the transpose of the matrices
    std::array<Eigen::IndexPair<int>, 1> transpose_product_dims = { Eigen::IndexPair<int>(0, 1) };
    Eigen::Tensor<int, 2> AtBt = a.contract(b, transpose_product_dims);
}

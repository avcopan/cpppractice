#include <ambit/tensor.h> // ambit::initialize, ambit::finalize, ambit::Tensor

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // build vector with two elements (kCore means store in core, as opposed to storing on disk)
  ambit::Tensor v = ambit::Tensor::build(ambit::kCore, "My Vector", {2});

  // build 2x3 matrix
  ambit::Tensor M = ambit::Tensor::build(ambit::kCore, "My Matrix", {2,3});

  // build 2x3x4 tensor
  ambit::Tensor T = ambit::Tensor::build(ambit::kCore, "My Tensor", {2,3,4});

  // set vector, matrix, and tensor elements equal to 1.0, 2.0, and 3.0, respectively
  v.set(1.0);
  M.set(2.0);
  T.set(3.0);

  // now, print each
  v.print();
  M.print();
  T.print();

  ambit::finalize();
}

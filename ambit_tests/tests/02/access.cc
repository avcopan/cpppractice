#include <ambit/print.h>  // ambit::print
#include <ambit/tensor.h> // abmit::initialize, ambit::finalize

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  ambit::Tensor A = ambit::Tensor::build(ambit::kCore, "A", {2,2});
  A.set(3.0);
  // @REQUEST: this vv is annoying -- access to data via standard integer indexing should not be hidden from the user
  for(size_t i=0; i<2; ++i)
    for(size_t j=0; j<2; ++j)
      ambit::print("A[2*%d + %d] = %15.7f\n", i, j, A.data()[2*i + j]);

  ambit::finalize();
}

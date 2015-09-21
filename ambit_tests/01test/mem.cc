#include <ambit/print.h>  // ambit::print
#include <ambit/tensor.h> // abmit::initialize, ambit::finalize

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  ambit::Tensor A = ambit::Tensor::build(ambit::kCore, "A", {2,2});
  ambit::Tensor B = A;
  B.set_name("B");
  A.print();
  B.print();
  A.set(3.0);
  A.print();
  B.print();

  ambit::finalize();
}

#include <ambit/print.h>  // ambit::print
#include <ambit/tensor.h> // ambit::initialize, ambit::finalize

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);
  ambit::print("Hello world!\n");
  ambit::finalize();
}

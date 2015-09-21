#include <ambit/print.h>
#include <ambit/tensor.h>

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);
  ambit::print("Hello world!\n");
  ambit::finalize();
}

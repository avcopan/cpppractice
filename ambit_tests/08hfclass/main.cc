#include "rhf.h"
#include <ambit/tensor.h>

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  RHF rhf("jobdata/psi.file.32", "jobdata/psi.file.33", "jobdata/psi.file.35");
  rhf.compute_energy();

  ambit::finalize();
}

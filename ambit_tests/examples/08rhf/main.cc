#include "rhf.h"          // RHF class
#include <ambit/tensor.h> // ambit::initialize, ambit::finalize, ambit::Tensor

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // declare RHF object (RHF constructor takes paths to the necessary Psi files)
  RHF rhf("jobdata/psi.file.32", "jobdata/psi.file.33", "jobdata/psi.file.35");

  // call compute_energy() function
  rhf.compute_energy();

  // get MO coefficients and orbital energies from rhf oject
  ambit::Tensor C = rhf.get_mocoefficients();
  ambit::Tensor e = rhf.get_orbital_energies();

  // print MO coefficients and orbital energies
  C.print();
  e.print();

  ambit::finalize();
}

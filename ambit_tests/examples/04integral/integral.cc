#include <ambit/tensor.h>          // abmit::initialize, ambit::finalize, ambit::Tensor
#include <ambit/io/io.h>           // ambit::io::File
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int nso;  chkpt.read("::Num. SO", &nso, 1); // read number of orbitals to int variable nso
  size_t norb = nso;                          // store as size_t instead of int

  // read overlap integrals from file PSIF_OEI = 35 and store them to ambit::Tensor S
  ambit::Tensor S = ambit::Tensor::build(ambit::kCore, "Overlap Integrals", {norb,norb});
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Overlap Ints", S);

  // print S
  S.print();

  ambit::finalize();
}

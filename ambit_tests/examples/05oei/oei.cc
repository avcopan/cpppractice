#include <ambit/tensor.h>          // abmit::initialize, ambit::finalize, ambit::Tensor
#include <ambit/io/io.h>           // ambit::io::File
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int nso;  chkpt.read("::Num. SO", &nso, 1);  size_t norb = nso;

  // read one electron integrals from file PSIF_OEI = 35
  ambit::Tensor S = ambit::Tensor::build(ambit::kCore, "Overlap"         , {norb,norb});
  ambit::Tensor T = ambit::Tensor::build(ambit::kCore, "Kinetic"         , {norb,norb});
  ambit::Tensor V = ambit::Tensor::build(ambit::kCore, "Potential"       , {norb,norb});
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Overlap Ints"         , S);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Kinetic Energy Ints"  , T);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Potential Energy Ints", V);

  // print them
  S.print();
  T.print();
  V.print();

  ambit::finalize();
}

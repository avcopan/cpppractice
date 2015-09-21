#include <ambit/print.h>           // ambit::print
#include <ambit/tensor.h>          // abmit::initialize, ambit::finalize
#include <ambit/io/io.h>           // ambit::io::File
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read dimension of one-e basis from file PSIF_CHKPT = 32
  ambit::io::File psif_chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int nso;  psif_chkpt.read("::Num. SO", &nso, 1);  size_t norb = nso;

  // read two electron integrals from file PSIF_TEI = 33
  ambit::Tensor G = ambit::Tensor::build(ambit::kCore, "Two-electron", {norb,norb,norb,norb});
  ambit::helpers::psi4::load_iwl("jobdata/psi.file.33", G);
  G.print();

  ambit::finalize();
}

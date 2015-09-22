#include <ambit/tensor.h>          // abmit::initialize, ambit::finalize, ambit::Tensor
#include <ambit/io/io.h>           // ambit::io::File
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_iwl

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read dimension of one-e basis from file PSIF_CHKPT = 32
  ambit::io::File chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int nso;  chkpt.read("::Num. SO", &nso, 1);  size_t norb = nso;

  // read two electron integrals from file PSIF_TEI = 33
  ambit::Tensor G = ambit::Tensor::build(ambit::kCore, "Two-electron", {norb,norb,norb,norb});
  ambit::helpers::psi4::load_iwl("jobdata/psi.file.33", G);

  // print G (large -- you may want to pipe it to a file, i.e. run ./tei.bin > printed_eris.txt)
  G.print();

  ambit::finalize();
}

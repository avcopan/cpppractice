#include <ambit/print.h>           // ambit::print
#include <ambit/tensor.h>          // abmit::initialize, ambit::finalize
#include <ambit/io/io.h>           // ambit::io::File
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File psif_chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int nso;  psif_chkpt.read("::Num. SO", &nso, 1);  size_t dim = nso;

  // read one electron integrals from file PSIF_OEI = 35
  ambit::Dimension rank2 = {dim, dim};
  ambit::Dimension rank4 = {dim, dim, dim, dim};
  ambit::Tensor S = ambit::Tensor::build(ambit::kCore, "Overlap Integrals", rank2);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Overlap Ints", S);
  S.print();

  ambit::finalize();
}

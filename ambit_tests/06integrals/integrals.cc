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

  // read one and two electron integrals from file PSIF_OEI = 35 and PSIF_TEI = 33
  ambit::Dimension rank2 = {dim, dim};
  ambit::Dimension rank4 = {dim, dim, dim, dim};
  ambit::Tensor S = ambit::Tensor::build(ambit::kCore, "Overlap"         , rank2);
  ambit::Tensor T = ambit::Tensor::build(ambit::kCore, "Kinetic"         , rank2);
  ambit::Tensor V = ambit::Tensor::build(ambit::kCore, "Potential"       , rank2);
  ambit::Tensor G = ambit::Tensor::build(ambit::kCore, "Two-electron"    , rank4);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Overlap Ints"         , S);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Kinetic Energy Ints"  , T);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Potential Energy Ints", V);
  ambit::helpers::psi4::load_iwl   ("jobdata/psi.file.33",                                   G);
  S.print();
  T.print();
  V.print();
  G.print();

  ambit::finalize();
}

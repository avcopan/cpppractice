#include <ambit/print.h>           // ambit::print
#include <ambit/tensor.h>          // abmit::initialize, ambit::finalize
#include <ambit/io/io.h>           // ambit::io::File
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix


int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File psif_chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int nso;  psif_chkpt.read("::Num. SO"                , &nso, 1);  size_t norb = nso;
  int occ;  psif_chkpt.read("::Closed shells per irrep", &occ, 1);  size_t nocc = occ;

  // read one and two electron integrals from file PSIF_OEI = 35 and PSIF_TEI = 33
  ambit::Dimension rank2 = {norb, norb};
  ambit::Dimension rank4 = {norb, norb, norb, norb};
  ambit::Tensor S = ambit::Tensor::build(ambit::kCore, "Overlap"     , {norb,norb}          );
  ambit::Tensor T = ambit::Tensor::build(ambit::kCore, "Kinetic"     , {norb,norb}          );
  ambit::Tensor V = ambit::Tensor::build(ambit::kCore, "Potential"   , {norb,norb}          );
  ambit::Tensor G = ambit::Tensor::build(ambit::kCore, "Two-electron", {norb,norb,norb,norb});
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Overlap Ints"         , S);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Kinetic Energy Ints"  , T);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Potential Energy Ints", V);
  ambit::helpers::psi4::load_iwl   ("jobdata/psi.file.33",                                   G);

  // Hartree-Fock
  ambit::Tensor  H = ambit::Tensor::build(ambit::kCore, "Core Hamiltonian"   , {norb,norb});
  ambit::Tensor  C = ambit::Tensor::build(ambit::kCore, "MO Coeffs"          , {norb,norb});
  ambit::Tensor xF = ambit::Tensor::build(ambit::kCore, "Fock (X Basis)"     , {norb,norb});
  ambit::Tensor xC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (X Basis)", {norb,norb});
  ambit::Tensor oC = ambit::Tensor::build(ambit::kCore, "Occ MO Coeffs"      , {norb,nocc});
  ambit::Tensor  X = S.power(-0.5);

  H("mu,nu") = T("mu,nu") + V("mu,nu");            // @REQUEST: overload +-*/ for unlabeled tensors as element-wise operations
  xF("m,n")  = X("mu,m") * H("mu,nu") * X("n,nu"); // @REQUEST: overload % as matmul
  xC = xF.syev(ambit::kAscending)["eigenvectors"];
  C("mu,p")  = X("mu,m") * xC("m,p");

  ambit::finalize();
}

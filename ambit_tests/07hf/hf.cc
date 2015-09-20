#include <ambit/print.h>           // ambit::print
#include <ambit/tensor.h>          // abmit::initialize, ambit::finalize
#include <ambit/io/io.h>           // ambit::io::File
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix
#include <cmath>


int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File psif_chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int    nso;  psif_chkpt.read("::Num. SO"                , &nso, 1);  size_t norb = nso;
  int    occ;  psif_chkpt.read("::Closed shells per irrep", &occ, 1);  size_t nocc = occ;
  double nuc;  psif_chkpt.read("::Nuclear rep. energy"    , &nuc, 1);  const double Enuc = nuc;

  // read one and two electron integrals from file PSIF_OEI = 35 and PSIF_TEI = 33
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
  ambit::Tensor  F = ambit::Tensor::build(ambit::kCore, "Fock"               , {norb,norb});
  ambit::Tensor  C = ambit::Tensor::build(ambit::kCore, "MO Coeffs"          , {norb,norb});
  ambit::Tensor  D = ambit::Tensor::build(ambit::kCore, "Density"            , {norb,norb});
  ambit::Tensor xF = ambit::Tensor::build(ambit::kCore, "Fock (X Basis)"     , {norb,norb});
  ambit::Tensor xC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (X Basis)", {norb,norb});
  ambit::Tensor oC = ambit::Tensor::build(ambit::kCore, "Occ MO Coeffs"      , {norb,nocc});
  ambit::Tensor  X = S.power(-0.5);                     // @REQUEST: implement power for ambit::BlockedTensor
  H ("mu,nu")  = T("mu,nu") + V("mu,nu");               // @REQUEST: overload + - * / for unlabeled tensors as element-wise operations
                                                        // @REQUEST: make string-free contract() function with tensordot-like arguments

  double E = 0.0; double E0 = 0.0;

  for(int iter = 0; iter < 100; ++iter)
  {
    F ("mu,nu")  = H("mu,nu");
    F ("mu,nu") += D("rh,si") * ( 2.0 * G("mu,nu,rh,si") - G("mu,rh,nu,si") );
    xF("mu,nu")  = X("mu,rh") * F("rh,si") * X("si,nu");  // @REQUEST: overload % as matmul
    xC = xF.syev(ambit::kAscending)["eigenvectors"];      // @REQUEST: diagonalization routine that returns eigenvectors by column
    C ("mu,p")   = X("mu,nu") * xC("p,nu"); // note that we're transposing the eigenvectors during the backtransformation
    oC({{0L,norb},{0L,nocc}}) = C({{0L,norb},{0L,nocc}}); // @REQUEST: WTF this has to be the ugliest way of slicing in the universe
                                                          //           should be able to do oC = C(all, {0L,nocc})
                                                          //           or at least oC = C.slice(all, {0L,nocc})
    D ("mu,nu")  = oC("mu,i") * oC("nu,i");

    E = D("mu,nu") * ( H("mu,nu") + F("mu,nu") ) + Enuc;
    ambit::print("@RHF-%-3d %20.15f %20.15f\n", iter, E, E - E0);
    if(std::fabs(E - E0) < 1.0e-12) break;
    E0 = E;
  }

  ambit::finalize();
}

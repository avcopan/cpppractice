#include <ambit/print.h>           // ambit::print
#include <ambit/tensor.h>          // abmit::initialize, ambit::finalize, ambit::Tensor
#include <ambit/io/io.h>           // ambit::io::File
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix, ambit::helpers::psi4::load_iwl
#include <cmath>                   // std::fabs


int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  /* BEGIN READ INTEGRALS */
  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int    nso;  chkpt.read("::Num. SO"                , &nso, 1);  size_t norb = nso;
  int    occ;  chkpt.read("::Closed shells per irrep", &occ, 1);  size_t nocc = occ;
  double nuc;  chkpt.read("::Nuclear rep. energy"    , &nuc, 1);  const double Enuc = nuc;
  // read one and two electron integrals from file PSIF_OEI = 35 and PSIF_TEI = 33
  ambit::Tensor S = ambit::Tensor::build(ambit::kCore, "Overlap"     , {norb,norb}          );
  ambit::Tensor T = ambit::Tensor::build(ambit::kCore, "Kinetic"     , {norb,norb}          );
  ambit::Tensor V = ambit::Tensor::build(ambit::kCore, "Potential"   , {norb,norb}          );
  ambit::Tensor G = ambit::Tensor::build(ambit::kCore, "Two-electron", {norb,norb,norb,norb});
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Overlap Ints"         , S);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Kinetic Energy Ints"  , T);
  ambit::helpers::psi4::load_matrix("jobdata/psi.file.35", "SO-basis Potential Energy Ints", V);
  ambit::helpers::psi4::load_iwl   ("jobdata/psi.file.33",                                   G);
  /* END READ INTEGRALS */

  /* BEGIN HARTREE FOCK CODE */
  // Build empty interemediate tensors
  ambit::Tensor  H = ambit::Tensor::build(ambit::kCore, "Core Hamiltonian"   , {norb,norb}); // H = T + V
  ambit::Tensor  F = ambit::Tensor::build(ambit::kCore, "Fock"               , {norb,norb}); // F = H + 2*J - K
  ambit::Tensor  C = ambit::Tensor::build(ambit::kCore, "MO Coeffs"          , {norb,norb}); // solution of F C = S C e
  ambit::Tensor  D = ambit::Tensor::build(ambit::kCore, "Density"            , {norb,norb}); // D = oC * oC.T
  ambit::Tensor oC = ambit::Tensor::build(ambit::kCore, "Occ MO Coeffs"      , {norb,nocc}); // columns [0, nocc) of C matrix
  ambit::Tensor xF = ambit::Tensor::build(ambit::kCore, "Fock (X Basis)"     , {norb,norb}); // F in orthogonalized AO basis
  ambit::Tensor xC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (X Basis)", {norb,norb}); // C in orthogonalized AO basis

  // Build and fill orthogonalizer, X = S^-1/2
  ambit::Tensor  X = S.power(-0.5);

  // Fill core Hamiltonian, H = T + V
  H ("mu,nu")  = T("mu,nu") + V("mu,nu");

  // Variables to store the energy (E0 will store the energy of the previous iteration in the loop)
  double E = 0.0; double E0 = 0.0;

  for(int iter = 0; iter < 100; ++iter) // hard-coded maxiter of 100
  {
    // build Fock matrix from density matrix, starting from core guess D = 0
    F("mu,nu")  = H("mu,nu");
    F("mu,nu") += D("rh,si") * ( 2.0 * G("mu,nu,rh,si") - G("mu,rh,nu,si") );
    // transform Fock mattrix to orthogonalized AO basis
    xF("mu,nu")  = X("mu,rh") * F("rh,si") * X("si,nu");
    // diagonalize xF and save eigenvectors as xC
    // (while transposing -- annoyingly, the eig vecs get returned as rows not columns)
    xC("mu,nu")  = xF.syev(ambit::kAscending)["eigenvectors"]("nu,mu");
    // backtransform eigenvectors to original AO basis
    C("mu,p")   = X("mu,nu") * xC("nu,p");
    // get occupied columns of C by slicing (in Python, this would be oC = C[:,0:nocc])
    oC({{0L,norb},{0L,nocc}}) = C({{0L,norb},{0L,nocc}});
    // build AO basis density matrix D_mu,nu = sum_i C_mu,i * C_nu,i
    D("mu,nu")  = oC("mu,i") * oC("nu,i");

    // compute RHF energy, E = trace( D*(H+F) ) + nuc. repulsion energy
    E = D("mu,nu") * ( H("nu,mu") + F("nu,mu") ) + Enuc;
    // print info (energy and energy change) for current iteration
    ambit::print("@RHF-%-3d %20.15f %20.15f\n", iter, E, E - E0);
    // check energy convergence and break out of the loop if converged
    if(std::fabs(E - E0) < 1.0e-12) break; // hard-coded E convergence of 10^-12
    // store current energy for comparison in the next interation
    E0 = E;
  }
  /* END HARTREE FOCK CODE */

  ambit::finalize();
}

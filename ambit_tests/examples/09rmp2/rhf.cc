#include "rhf.h"
#include <ambit/tensor.h>          // ambit::initialize, ambit::finalize, ambit::Tensor
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix, ambit::helpers::psi4::load_iwl
#include <ambit/print.h>           // ambit::print
#include <cmath>                   // std::fabs
#include <string>                  // std::string

/* CONSTRUCTOR */
RHF::RHF(const std::string& file32path, const std::string& file33path, const std::string& file35path)
{
  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File chkpt(file32path, ambit::io::kOpenModeOpenExisting);
  int    nso;  chkpt.read("::Num. SO"                , &nso, 1);  _norb = nso;
  int    occ;  chkpt.read("::Closed shells per irrep", &occ, 1);  _nocc = occ;
  double nuc;  chkpt.read("::Nuclear rep. energy"    , &nuc, 1);  _Enuc = nuc;

  // read one and two electron integrals from file PSIF_OEI = 35 and PSIF_TEI = 33
  ambit::Tensor S = ambit::Tensor::build(ambit::kCore, "Overlap"     ,             {_norb,_norb});
  ambit::Tensor T = ambit::Tensor::build(ambit::kCore, "Kinetic"     ,             {_norb,_norb});
  ambit::Tensor V = ambit::Tensor::build(ambit::kCore, "Potential"   ,             {_norb,_norb});
  ambit::Tensor G = ambit::Tensor::build(ambit::kCore, "Two-electron", {_norb,_norb,_norb,_norb});
  ambit::helpers::psi4::load_matrix(file35path, "SO-basis Overlap Ints"         ,  S);
  ambit::helpers::psi4::load_matrix(file35path, "SO-basis Kinetic Energy Ints"  ,  T);
  ambit::helpers::psi4::load_matrix(file35path, "SO-basis Potential Energy Ints",  V);
  ambit::helpers::psi4::load_iwl   (file33path,                                    G);
  _e = ambit::Tensor::build(ambit::kCore, "Orbital energies"   ,                   {_norb});
  _H = ambit::Tensor::build(ambit::kCore, "Core Hamiltonian"   ,             {_norb,_norb});
  _F = ambit::Tensor::build(ambit::kCore, "Fock"               ,             {_norb,_norb});
  _C = ambit::Tensor::build(ambit::kCore, "MO Coeffs"          ,             {_norb,_norb});
  _D = ambit::Tensor::build(ambit::kCore, "Density"            ,             {_norb,_norb});
  _G = ambit::Tensor::build(ambit::kCore, "Two-electron (Phys)", {_norb,_norb,_norb,_norb});
  _X = S.power(-0.5);                    // build orthogonalizer
  _H("mu,nu") = T("mu,nu") + V("mu,nu"); // build core Hamiltonian
  _G("mu,nu,rh,si") = G("mu,rh,nu,si");  // convert two-electron integrals to physicist's notation
}

/* RHF CODE */
double RHF::compute_energy()
{
  ambit::Tensor xF = ambit::Tensor::build(ambit::kCore, "Fock (X Basis)"     , {_norb,_norb});
  ambit::Tensor xC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (X Basis)", {_norb,_norb});
  ambit::Tensor oC = ambit::Tensor::build(ambit::kCore, "Occ MO Coeffs"      , {_norb,_nocc});

  double E = 0;

  for(int iter = 0; iter < 100; ++iter)
  {
    // build Fock matrix from density matrix, starting from core guess D = 0
    _F("mu,nu")  = _H("mu,nu");
    _F("mu,nu") += _D("rh,si") * ( 2.0 * _G("mu,rh,nu,si") - _G("mu,rh,si,nu") );
    // transform Fock mattrix to orthogonalized AO basis
    xF("mu,nu")  = _X("mu,rh") * _F("rh,si") * _X("si,nu");
    // diagonalize xF and save eigenvectors as xC
    // (while transposing -- annoyingly, the eig vecs get returned as rows not columns)
    xC("mu,nu")  = xF.syev(ambit::kAscending)["eigenvectors"]("nu,mu");
    // backtransform eigenvectors to original AO basis
    _C("mu,p")   = _X("mu,nu") * xC("nu,p");
    // get occupied columns of C by slicing (in Python, this would be oC = C[:,0:nocc])
    oC({{0L,_norb},{0L,_nocc}}) = _C({{0L,_norb},{0L,_nocc}});
    // build AO basis density matrix D_mu,nu = sum_i C_mu,i * C_nu,i
    _D("mu,nu")  = oC("mu,i") * oC("nu,i");

    // compute RHF energy, E = trace( D*(H+F) ) + nuc. repulsion energy
    _E = _D("mu,nu") * ( _H("mu,nu") + _F("mu,nu") ) + _Enuc;
    // print info (energy and energy change) for current iteration
    ambit::print("@RHF-%-3d %20.15f %20.15f\n", iter, _E, _E - E);
    // check energy convergence and break out of the loop if converged
    if(std::fabs(_E - E) < 1.0e-12) break;  E = _E; // store energy for next loop comparison
  }

  // store the orbital energies to _e
  _e = xF.syev(ambit::kAscending)["eigenvalues"];
  // set the name to something more intuitive
  _e.set_name("Orbital energies");

  // return the RHF energy
  return _E;
}

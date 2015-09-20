#include "rhf.h"
#include <ambit/tensor.h>          // ambit::initialize, ambit::finalize, ambit::Tensor
#include <ambit/helpers/psi4/io.h> // ambit::helpers::psi4::load_matrix
#include <ambit/print.h>           // ambit::print
#include <cmath>
#include <string>                  // std::string

RHF::RHF(const std::string& file32path, const std::string& file33path, const std::string& file35path)
{
  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File psif_chkpt(file32path, ambit::io::kOpenModeOpenExisting);
  int    nso;  psif_chkpt.read("::Num. SO"                , &nso, 1);  _norb = nso;
  int    occ;  psif_chkpt.read("::Closed shells per irrep", &occ, 1);  _nocc = occ;
  double nuc;  psif_chkpt.read("::Nuclear rep. energy"    , &nuc, 1);  _Enuc = nuc;

  // read one and two electron integrals from file PSIF_OEI = 35 and PSIF_TEI = 33
  ambit::Tensor S = ambit::Tensor::build(ambit::kCore, "Overlap"     , {_norb,_norb});
  ambit::Tensor T = ambit::Tensor::build(ambit::kCore, "Kinetic"     , {_norb,_norb});
  ambit::Tensor V = ambit::Tensor::build(ambit::kCore, "Potential"   , {_norb,_norb});
  _G = ambit::Tensor::build(ambit::kCore, "Two-electron", {_norb,_norb,_norb,_norb});
  ambit::helpers::psi4::load_matrix(file35path, "SO-basis Overlap Ints"         ,  S);
  ambit::helpers::psi4::load_matrix(file35path, "SO-basis Kinetic Energy Ints"  ,  T);
  ambit::helpers::psi4::load_matrix(file35path, "SO-basis Potential Energy Ints",  V);
  ambit::helpers::psi4::load_iwl   (file33path,                                   _G);
  _H = ambit::Tensor::build(ambit::kCore, "Core Hamiltonian", {_norb,_norb});
  _F = ambit::Tensor::build(ambit::kCore, "Fock"            , {_norb,_norb});
  _C = ambit::Tensor::build(ambit::kCore, "MO Coeffs"       , {_norb,_norb});
  _D = ambit::Tensor::build(ambit::kCore, "Density"         , {_norb,_norb});
  _X = S.power(-0.5);                     // @REQUEST: implement power for ambit::BlockedTensor
  _H("mu,nu")  = T("mu,nu") + V("mu,nu"); // @REQUEST: overload + - * / for unlabeled tensors as element-wise operations
                                          // @REQUEST: make string-free contract() function with tensordot-like arguments
}

double RHF::compute_energy()
{
  ambit::Tensor xF = ambit::Tensor::build(ambit::kCore, "Fock (X Basis)"     , {_norb,_norb});
  ambit::Tensor xC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (X Basis)", {_norb,_norb});
  ambit::Tensor oC = ambit::Tensor::build(ambit::kCore, "Occ MO Coeffs"      , {_norb,_nocc});

  double E = 0;

  for(int iter = 0; iter < 100; ++iter)
  {
    _F("mu,nu")  = _H("mu,nu");
    _F("mu,nu") += _D("rh,si") * ( 2.0 * _G("mu,nu,rh,si") - _G("mu,rh,nu,si") );
    xF("mu,nu")  = _X("mu,rh") * _F("rh,si") * _X("si,nu");             // @REQUEST: overload % as matmul
    xC("mu,nu")  = xF.syev(ambit::kAscending)["eigenvectors"]("nu,mu"); // @REQUEST: diagonalization routine that returns
                                                                        //           eigenvectors by column
    _C("mu,p")   = _X("mu,nu") * xC("nu,p");
    oC({{0L,_norb},{0L,_nocc}}) = _C({{0L,_norb},{0L,_nocc}}); // @REQUEST: WTF this has to be the ugliest way of slicing in the universe
                                                               //           should be able to do oC = C(all, {0L,nocc})
                                                               //           or at least oC = C.slice(all, {0L,nocc})
    _D("mu,nu")  = oC("mu,i") * oC("nu,i");

    _E = _D("mu,nu") * ( _H("mu,nu") + _F("mu,nu") ) + _Enuc;

    ambit::print("@RHF-%-3d %20.15f %20.15f\n", iter, _E, _E - E);
    if(std::fabs(_E - E) < 1.0e-12) break;  E = _E;
  }

  return _E;
}

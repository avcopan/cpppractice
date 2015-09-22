#include "rhf.h"          // RHF class
#include <ambit/tensor.h> // ambit::initialize, ambit::finalize, ambit::Tensor
#include <ambit/print.h>  // ambit::print

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // Call RHF constructor with paths to necessary Psi files
  RHF rhf("jobdata/psi.file.32", "jobdata/psi.file.33", "jobdata/psi.file.35");

  // Run RHF code, which filles MO coefficients and such with their correct values
  rhf.compute_energy();

  // grab the necessary data from RHF object
  size_t norb = rhf.get_norb();
  size_t nocc = rhf.get_nocc();
  size_t nvir = norb - nocc;
  ambit::Tensor e  = rhf.get_orbital_energies();
  ambit::Tensor C  = rhf.get_mocoefficients();
  ambit::Tensor G  = rhf.get_eri_phys();

  // Build empty intermediates for this MP2 code
  ambit::Tensor oe = ambit::Tensor::build(ambit::kCore, "Orbital energies (o block)"        ,                {nocc});
  ambit::Tensor ve = ambit::Tensor::build(ambit::kCore, "Orbital energies (v block)"        ,                {nvir});
  ambit::Tensor oC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (o block)"               ,           {norb,nocc});
  ambit::Tensor vC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (v block)"               ,           {norb,nvir});
  ambit::Tensor g  = ambit::Tensor::build(ambit::kCore, "MO Two-electron (Phys, oovv block)", {nocc,nocc,nvir,nvir});
  ambit::Tensor D  = ambit::Tensor::build(ambit::kCore, "1/(e_i + e_j - e_a - e_b)"         , {nocc,nocc,nvir,nvir});
  ambit::Tensor T2 = ambit::Tensor::build(ambit::kCore, "MP2 Doubles Amplitues"             , {nocc,nocc,nvir,nvir});

  // Fill oe, ve, oC, and vC with occ/vir slices of e and C
  oe.slice(e, {          {0L,nocc}}, {          {0L  ,nocc}});
  ve.slice(e, {          {0L,nvir}}, {          {nocc,norb}});
  oC.slice(C, {{0L,norb},{0L,nocc}}, {{0L,norb},{0L  ,nocc}});
  vC.slice(C, {{0L,norb},{0L,nvir}}, {{0L,norb},{nocc,norb}});

  // construct D_ijab = 1 / (e_i + e_j - e_a - e_b) -- unfortunately, you have to
  // access the underlying data pointers to do this.  Hopefully there will eventually
  // be a better way to do this.
  for(size_t i=0; i<nocc; ++i)
    for(size_t j=0; j<nocc; ++j)
      for(size_t a=0; a<nvir; ++a)
        for(size_t b=0; b<nvir; ++b)
          D.data()[nocc*nvir*nvir*i + nvir*nvir*j + nvir*a + b] = 1. / ( oe.data()[i] + oe.data()[j] - ve.data()[a] - ve.data()[b] );
  // ambit::Tensors store tensor elements by global index, so the i1,i2,i3 element
  // of an n1 x n2 x n3 tensor T is T[ n2*n3*i1 + n3*i2 + i3 ]

  // inefficient (n^8) orbital transformation
  g("i,j,a,b") = oC("mu,i") * oC("nu,j") * vC("rh,a") * vC("si,b") * G("mu,nu,rh,si");

  // build MP2 T2 amplitudes, t_ijab = <ij|ab> / (e_i + e_j - e_a - e_b)
  T2("i,j,a,b") = D("i,j,a,b") * g("i,j,a,b");

  // compute MP2 correlation energy, E = sum_ijab t_ijab ( 2*<ij|ab> - <ij|ba> )
  double E = T2("i,j,a,b") * ( 2 * g("i,j,a,b") - g("i,j,b,a") );

  // print the energy
  ambit::print("@MP2 Correlation Energy = %20.17f\n", E);

  ambit::finalize();
}

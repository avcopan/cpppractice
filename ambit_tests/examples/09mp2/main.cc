#include "rhf.h"
#include <ambit/tensor.h>
#include <ambit/print.h>

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  RHF rhf("jobdata/psi.file.32", "jobdata/psi.file.33", "jobdata/psi.file.35");
  rhf.compute_energy();

  size_t norb = rhf.get_norb();  size_t nocc = rhf.get_nocc();  size_t nvir = norb - nocc;
  ambit::Tensor e  = rhf.get_orbital_energies();
  ambit::Tensor C  = rhf.get_mocoefficients();
  ambit::Tensor G  = rhf.get_eri_phys();
  ambit::Tensor oe = ambit::Tensor::build(ambit::kCore, "Orbital energies (o block)"        ,                {nocc});
  ambit::Tensor ve = ambit::Tensor::build(ambit::kCore, "Orbital energies (v block)"        ,                {nvir});
  ambit::Tensor oC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (o block)"               ,           {norb,nocc});
  ambit::Tensor vC = ambit::Tensor::build(ambit::kCore, "MO Coeffs (v block)"               ,           {norb,nvir});
  ambit::Tensor g  = ambit::Tensor::build(ambit::kCore, "MO Two-electron (Phys, oovv block)", {nocc,nocc,nvir,nvir});
  ambit::Tensor D  = ambit::Tensor::build(ambit::kCore, "ei+ej-ea-eb"                       , {nocc,nocc,nvir,nvir});
  ambit::Tensor T2 = ambit::Tensor::build(ambit::kCore, "Doubles Amplitues"                 , {nocc,nocc,nvir,nvir});

  // @REQUEST: this v throws an error for rank 1, but works for rank >1
  //oe({{0L,nocc}}) = e({{0L  ,nocc}});
  //ve({{0L,nvir}}) = e({{nocc,norb}});
  //oC({{0L,norb},{0L,nocc}}) = C({{0L,norb},{0L  ,nocc}});
  //vC({{0L,norb},{0L,nvir}}) = C({{0L,norb},{nocc,norb}});
  // @REQUEST: also, this definition of slicing is extremely unintuitive in my opinion
  //           IMO X.slice(Xranges,ranges) should *return* that slice of X instead of
  //           X.slice(Y, Xranges, Yranges) which *fills* X with a slice of Y
  //           since object.slice() implies that one is taking a slice of object
  oe.slice(e, {          {0L,nocc}}, {          {0L  ,nocc}});
  ve.slice(e, {          {0L,nvir}}, {          {nocc,norb}});
  oC.slice(C, {{0L,norb},{0L,nocc}}, {{0L,norb},{0L  ,nocc}});
  vC.slice(C, {{0L,norb},{0L,nvir}}, {{0L,norb},{nocc,norb}});

  // @REQUEST: there ought to be some simple way of doing the following:
  //D("i,j,a,b") = oe("i") + oe("j") - ve("a") - ve("b");
  for(size_t i=0; i<nocc; ++i) // this
    for(size_t j=0; j<nocc; ++j) // is
      for(size_t a=0; a<nvir; ++a) // the
        for(size_t b=0; b<nvir; ++b) // worst
          D.data()[nocc*nvir*nvir*i + nvir*nvir*j + nvir*a + b] = 1 / ( oe.data()[i] + oe.data()[j] + ve.data()[a] + ve.data()[b] );

  // @REQUEST: this v throws error: no match for ‘operator*’ (operand types are ‘ambit::LabeledTensor’ and ‘ambit::LabeledTensorProduct’)
  //           IMO this code should compute the n^5 integral transformation -- each () defining an intermediate
  //g("p,q,r,s") = C("mu,p") * ( C("nu,q") * ( C("rh,r") * ( C("si,s") * G("mu,nu,rh,si") )));
  g("i,j,a,b") = oC("mu,i") * oC("nu,j") * vC("rh,a") * vC("si,b") * G("mu,nu,rh,si");

  T2("i,j,a,b") = D("i,j,a,b") * g("i,j,a,b");
  double E = T2("i,j,a,b") * ( 2 * g("i,j,a,b") - g("i,j,b,a") );
  ambit::print("%15.7f\n", E);

  ambit::finalize();
}

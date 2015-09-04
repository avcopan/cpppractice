#include <integrals.h>
#include <libpsio/psio.hpp>
#include <libmints/mints.h>

namespace plugin {

SOIntegrals::SOIntegrals(psi::MintsHelper mints)
{
  psi::outfile->Printf("nbf = %d\n", mints.basisset()->nbf());
  psi::SharedMatrix S = mints.ao_overlap();
  psi::SharedMatrix T = mints.ao_kinetic();
  psi::SharedMatrix V = mints.ao_potential();
  psi::SharedMatrix G = mints.ao_eri();

  psi::Dimension dim = mints.sobasisset()->dimension();
  dim.print();

  psi::SharedMatrix M(new psi::Matrix(dim,dim));
  //M->print();
  //S->print();

  M->apply_symmetry(S, mints.petite_list()->aotoso());
  //M->print();

  psi::SharedMatrix S2 = mints.ao_overlap(mints.sobasisset(), mints.sobasisset());
  S2->print();

}

}

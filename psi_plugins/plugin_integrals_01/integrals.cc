#include <libmints/mints.h>
#include <boost/shared_ptr.hpp>
#include "integrals.h"

namespace plugin {

Integrals::Integrals()
{
  psi::outfile->Printf("Hello?\n");
  psi::MintsHelper mints;
  _intfactory = mints.integral();
  // initialize AO matrix factory
  int nbf[] = { mints.nbf() };
  _ao_matfactory.init_with(1, nbf, nbf);
  // initialize SO matrix factory
  psi::Dimension nbfpi = mints.sobasisset()->dimension();
  _so_matfactory.init_with(nbfpi, nbfpi);
  // test a few to see if it's working
  psi::SharedMatrix M1(_ao_matfactory.create_matrix("M1"));
  psi::SharedMatrix M2(_so_matfactory.create_matrix("M2"));
  M1->print();
  M2->print();
}


}

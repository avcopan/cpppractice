#include <integrals.h>
#include <libpsio/psio.hpp>
#include <libmints/mints.h>

namespace plugin {

SOIntegrals::SOIntegrals(psi::MintsHelper mints)
{
  psi::outfile->Printf("nbf = %d\n", mints.basisset()->nbf());
  psi::SharedMatrix S = mints.so_overlap();
  S->print();
}

}

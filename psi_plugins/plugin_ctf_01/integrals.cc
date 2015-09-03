#include "integrals.h"
#include <ctf.hpp>
#include <libmints/mints.h>

namespace plugin {

boost::shared_ptr<CTF::Tensor<> > Integrals::ao_overlap()
{
  int dim[] = {_mints.nbf(), _mints.nbf()};
  int sym[] = {_SYM::SY, _SYM::NS};
  boost::shared_ptr<CTF::Tensor<> > S1(new CTF::Tensor<>(2, dim, sym, *_world));
  psi::SharedMatrix                 S2 = _mints.ao_overlap();

  CTF::Tensor<> S = *S1;

  S.print(stdout);

  S2->print();
  return S1;
}

}

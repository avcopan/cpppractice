#include "orbitals.h"
#include <ctf.hpp>
#include <boost/shared_ptr.hpp>
#include <libmints/mints.h>

namespace plugin {

Orbitals::Orbitals(boost::shared_ptr<CTF::World> world, boost::shared_ptr<psi::Wavefunction> wfn) : _world(world), _wfn(wfn)
{
  _wfn->S()->print();
}

}

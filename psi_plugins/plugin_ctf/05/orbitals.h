#include <ctf.hpp>
#include <libmits/mints.h>

namespace plugin {

class Orbitals {
  private:
    boost::shared_ptr<psi::Wavefunction> wfn;
    CTF::World * _world;
  public:
    Orbitals(CTF::World&, boost::shared_ptr<psi::Wavefunction>);
};

}

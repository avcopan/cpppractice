#include <ctf.hpp>
#include <boost/shared_ptr.hpp>
#include <libmints/mints.h>

namespace plugin {

class Orbitals {
  private:
    boost::shared_ptr<CTF::World>        _world;
    boost::shared_ptr<psi::Wavefunction> _wfn;
  public:
    Orbitals(boost::shared_ptr<CTF::World>, boost::shared_ptr<psi::Wavefunction>);
};

}

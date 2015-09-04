#include <ctf.hpp>
#include <libmints/mints.h>

namespace plugin {

class Integrals {
  private:
    enum _SYM : int { NS, SY, AS, SH };
    psi::MintsHelper _mints;
    CTF::World *     _world;
  public:
    Integrals(CTF::World& world) : _world(&world) {};
    boost::shared_ptr<CTF::Tensor<> > ao_overlap();
};

}

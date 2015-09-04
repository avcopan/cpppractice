#include <ctf.hpp>
#include <libmints/mints.h>

namespace plugin {

class Integrals {
  private:
    psi::MintsHelper _mints;
    boost::shared_ptr<CTF::World> _world;
  public:
    Integrals(boost::shared_ptr<CTF::World> world) : _world(world) {};
    CTF::Tensor<> ao_overlap();
    CTF::Tensor<> ao_kinetic();
    CTF::Tensor<> ao_potential();
    CTF::Tensor<> ao_eri();
    CTF::Tensor<> oei_to_ctf_tensor(psi::SharedMatrix);
    CTF::Tensor<> get_eri();
};

}

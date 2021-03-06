#include <ctf.hpp>
#include <libmints/mints.h>

namespace plugin {

class Integrals {
  private:
    psi::MintsHelper _mints;
    CTF::World *     _world;
  public:
    Integrals(CTF::World& world) : _world(&world) {};
    CTF::Tensor<> ao_overlap();
    CTF::Tensor<> ao_kinetic();
    CTF::Tensor<> ao_potential();
    CTF::Tensor<> oei_to_ctf_tensor(psi::SharedMatrix);

    void get_eri();
};

}

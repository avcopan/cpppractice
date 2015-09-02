#include <libmints/mints.h>
#include <boost/shared_ptr.hpp>

namespace plugin {

class Integrals {
  private:
    boost::shared_ptr<psi::IntegralFactory> _intfactory;
    psi::MatrixFactory   _ao_matfactory;
    psi::MatrixFactory   _so_matfactory;
  public:
    Integrals();
};

}

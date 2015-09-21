#include <ambit/tensor.h>  // ambit::initialize, ambit::finalize, ambit::Tensor
#include <string>          // std::string

class RHF {
  private:
    size_t        _norb, _nocc;
    double        _E, _Enuc;
    ambit::Tensor _G, _H, _F, _C, _D, _X;
  public:
    RHF(const std::string&, const std::string&, const std::string&);
    double compute_energy();
};

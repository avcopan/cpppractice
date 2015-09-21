#include <ambit/tensor.h>  // ambit::initialize, ambit::finalize, ambit::Tensor
#include <string>          // std::string

class RHF {
  private:
    size_t        _norb, _nocc;
    double        _E, _Enuc;
    ambit::Tensor _G, _H, _F, _C, _D, _X, _e;
  public:
    RHF(const std::string&, const std::string&, const std::string&);
    double compute_energy();
    size_t        get_norb()             { return _norb; }
    size_t        get_nocc()             { return _nocc; }
    ambit::Tensor get_eri_phys()         { return    _G; }
    ambit::Tensor get_core_hamiltonian() { return    _H; }
    ambit::Tensor get_fock()             { return    _F; }
    ambit::Tensor get_hf_density()       { return    _D; }
    ambit::Tensor get_orthogonalizer()   { return    _X; }
    ambit::Tensor get_mocoefficients()   { return    _C; }
    ambit::Tensor get_orbital_energies() { return    _e; }
};

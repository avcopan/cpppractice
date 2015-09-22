#include <ambit/tensor.h>  // ambit::initialize, ambit::finalize, ambit::Tensor
#include <string>          // std::string

class RHF {
  private:
    size_t        _norb, _nocc;
    double        _E, _Enuc;
    ambit::Tensor _G, _H, _F, _C, _D, _X, _e;
  public:

    /* constructor -- takes paths to Psi files 32, 33, and 35 as argument */
    RHF(const std::string&, const std::string&, const std::string&);

    /* compute_energy() does RHF and fills class variables (MO coeffs, orb energies, etc.) */
    double compute_energy();

    /* these can be used to grab RHF object data in post-HF code */
    size_t        get_norb()             { return _norb; } // total number of orbitals = number of basis functions
    size_t        get_nocc()             { return _nocc; } // number of occupied orbitals = number of electrons / 2
    ambit::Tensor get_eri_phys()         { return    _G; } // two-electron integrals, physicist's notation <mu nu|rh si>
    ambit::Tensor get_core_hamiltonian() { return    _H; } // core Hamiltonian H = T + V
    ambit::Tensor get_fock()             { return    _F; } // Fock matrix F = H + 2*J - K
    ambit::Tensor get_hf_density()       { return    _D; } // RHF density matrix
    ambit::Tensor get_orthogonalizer()   { return    _X; } // orthogonalizer X = S^-1/2, where S is overlap matrix
    ambit::Tensor get_mocoefficients()   { return    _C; } // MO coefficients -- solutions of   FC = SCe
    ambit::Tensor get_orbital_energies() { return    _e; } // orbital energies -- diagonal elements of ^
};

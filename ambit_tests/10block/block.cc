#include <ambit/print.h>          // ambit::print
#include <ambit/tensor.h>         // abmit::initialize, ambit::finalize
#include <ambit/blocked_tensor.h> // ambit::BlockedTensor
#include <ambit/io/io.h>          // ambit::io::File
#include <vector>                 // std::vector
#include <numeric>                // std::iota

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read number of orbitals from file PSIF_CHKPT = 32
  ambit::io::File psif_chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  int nso;  psif_chkpt.read("::Num. SO"                , &nso, 1);  size_t norb = nso;  size_t null = 0;
  int occ;  psif_chkpt.read("::Closed shells per irrep", &occ, 1);  size_t nocc = occ;  size_t nvir = norb - nocc;

  // create occ, vir, and ao ranges
  std::vector<size_t> occ_range(nocc);
  std::vector<size_t> vir_range(nvir);
  std::vector<size_t>  ao_range(norb);
  std::iota(occ_range.begin(), occ_range.end(), null);
  std::iota(vir_range.begin(), vir_range.end(), nocc);
  std::iota( ao_range.begin(),  ao_range.end(), null);

  // declare occ, vir, gen, and AO spaces
  ambit::BlockedTensor::add_mo_space("o",     "i,j,k,l", occ_range, ambit::AlphaSpin);
  ambit::BlockedTensor::add_mo_space("v",     "a,b,c,d", vir_range, ambit::AlphaSpin);
  ambit::BlockedTensor::add_mo_space("a", "mu,nu,rh,si",  ao_range, ambit::AlphaSpin);
  ambit::BlockedTensor::add_composite_mo_space("g",     "p,q,r,s", {"o","v"});

  ambit::finalize();
}

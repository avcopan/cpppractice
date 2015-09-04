#include "integrals.h"
#include <ctf.hpp>
#include <libmints/mints.h>
#include <vector>

namespace plugin {

CTF::Tensor<> Integrals::ao_overlap()   { return oei_to_ctf_tensor(_mints.ao_overlap()  ); }
CTF::Tensor<> Integrals::ao_kinetic()   { return oei_to_ctf_tensor(_mints.ao_kinetic()  ); }
CTF::Tensor<> Integrals::ao_potential() { return oei_to_ctf_tensor(_mints.ao_potential()); }

CTF::Tensor<> Integrals::oei_to_ctf_tensor(psi::SharedMatrix M)
{
  // create index vector and value vector to be read into CTF::Tensor
  std::vector<int64_t> indices;
  std::vector<double>  values;
  for(int64_t i = 0; i < M->rowdim(); ++i)
    for(int64_t j = i; j < M->coldim(); ++j)
    {
      indices.push_back(i + M->rowdim() * j);
      values.push_back(M->get(i,j));
    }

  // now, build and fill CTF::Tensor
  int dim[] = { M->rowdim(), M->coldim() };
  int sym[] = {           1,           0 };
  CTF::Tensor<> T(2, dim, sym, *_world);
  T[indices] = values;

  return T;
}

}

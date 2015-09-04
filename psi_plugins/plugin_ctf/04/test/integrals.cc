#include "integrals.h"
#include <ctf.hpp>
#include <libmints/mints.h>
#include <vector>

namespace plugin {

CTF::Tensor<> Integrals::ao_overlap()   { return oei_to_ctf_tensor(_mints.ao_overlap()  ); }
CTF::Tensor<> Integrals::ao_kinetic()   { return oei_to_ctf_tensor(_mints.ao_kinetic()  ); }
CTF::Tensor<> Integrals::ao_potential() { return oei_to_ctf_tensor(_mints.ao_potential()); }
CTF::Tensor<> Integrals::ao_eri()       { return get_eri(); }

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

CTF::Tensor<> Integrals::get_eri()
{
  int nbf = _mints.nbf();
  boost::shared_ptr<psi::IntegralFactory> intfactory = _mints.integral();

  std::vector<int64_t> indices;
  std::vector<double>  values;

  boost::shared_ptr<psi::TwoBodyAOInt> eri(intfactory->eri());
  const double* buffer = eri->buffer();
  psi::AOShellCombinationsIterator shell_iter = intfactory->shells_iterator();
  for(shell_iter.first(); shell_iter.is_done() == false; shell_iter.next())
  {
    eri->compute_shell(shell_iter);
    psi::AOIntegralsIterator int_iter = shell_iter.integrals_iterator();
    for(int_iter.first(); int_iter.is_done() == false; int_iter.next())
    {
      int64_t i = int_iter.i(); int64_t j = int_iter.j(); int64_t k = int_iter.k(); int64_t l = int_iter.l();
      indices.push_back(i + nbf*j + nbf*nbf*k + nbf*nbf*nbf*l);
      values.push_back( buffer[int_iter.index()] );
      if( i != k || j != l )
      {
        indices.push_back(k + nbf*l + nbf*nbf*i + nbf*nbf*nbf*j);
        values.push_back( buffer[int_iter.index()] );
      }
    }
  }

  // now, build and fill CTF::Tensor
  int dim[] = { nbf, nbf, nbf, nbf };
  int sym[] = {   1,   0,   1,   0 };
  CTF::Tensor<> T(4, dim, sym, *_world);
  T[indices] = values;

  T.print(stdout);

  return T;
}

}

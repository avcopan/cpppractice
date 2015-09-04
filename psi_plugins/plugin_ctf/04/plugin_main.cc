#include <libplugin/plugin.h>
#include <liboptions/liboptions.h>
#include <libpsio/psio.hpp>

#include "integrals.h"
#include <ctf.hpp>

INIT_PLUGIN

extern "C" 
int read_options(std::string name, psi::Options& options) { return false; }


/* PLUGIN MAIN() */
extern "C" 
psi::PsiReturnType plugin_main(psi::Options& options)
{

  /* Call my code: make UHF obj and ask it to compute something */
  CTF::World world;
  plugin::Integrals integrals(world);

  CTF::Tensor<> S = integrals.ao_overlap();
  CTF::Tensor<> T = integrals.ao_kinetic();
  CTF::Tensor<> V = integrals.ao_potential();
  CTF::Tensor<> G = integrals.ao_eri();

  return psi::Success;
}

#include <libplugin/plugin.h>
#include <psi4-dec.h>
#include <libparallel/parallel.h>
#include <liboptions/liboptions.h>
#include <libmints/mints.h>
#include <libpsio/psio.hpp>

INIT_PLUGIN

extern "C" 
int read_options(std::string name, psi::Options& options) { return false; }

extern "C" 
psi::PsiReturnType plugger(psi::Options& options)
{
  /* Your code goes here */

  return psi::Success;
}

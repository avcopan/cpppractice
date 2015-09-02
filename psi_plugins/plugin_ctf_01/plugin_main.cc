#include <libplugin/plugin.h>
#include <liboptions/liboptions.h>
#include <libpsio/psio.hpp>

#include "integrals.h"

INIT_PLUGIN

extern "C" 
int read_options(std::string name, psi::Options& options) { return false; }


/* PLUGIN MAIN() */
extern "C" 
psi::PsiReturnType plugin_main(psi::Options& options)
{

  /* Call my code: make UHF obj and ask it to compute something */
  plugin::Integrals integrals;

  return psi::Success;
}

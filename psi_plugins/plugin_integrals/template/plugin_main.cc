#include <libplugin/plugin.h>
#include <liboptions/liboptions.h>
#include <libmints/mints.h>
#include <libpsio/psio.hpp>
#include <integrals.h>

INIT_PLUGIN

extern "C" 
int read_options(std::string name, psi::Options& options) { return false; }

/* MAIN() */
extern "C" 
psi::PsiReturnType plugin_main(psi::Options& options)
{

  /* Your code goes here */
  /* BEGIN SAMPLE */
  psi::outfile->Printf("Hello World!\n");
  psi::MintsHelper mints;
  plugin::SOIntegrals sointegrals(mints);
  /* END SAMPLE */

  return psi::Success;
}

#include <libplugin/plugin.h>
#include <liboptions/liboptions.h>
#include <libmints/mints.h>
#include <libpsio/psio.hpp>

INIT_PLUGIN

extern "C" 
int read_options(std::string name, psi::Options& options) { return false; }


/* PLUGIN MAIN() */
extern "C" 
psi::PsiReturnType plugin_main(psi::Options& options)
{

  /* Your code goes here */
  /* BEGIN SAMPLE */
  psi::outfile->Printf("Hello World!\n");
  boost::shared_ptr<psi::Wavefunction> uhf = psi::Process::environment.wavefunction();
  uhf->S()->print();
  uhf->H()->print();
  uhf->Ca()->print();
  /* END SAMPLE */

  return psi::Success;
}

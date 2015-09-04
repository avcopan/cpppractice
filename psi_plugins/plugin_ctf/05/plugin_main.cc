#include <libplugin/plugin.h>
#include <liboptions/liboptions.h>
#include <libmints/mints.h>
#include <libpsio/psio.hpp>

#include <ctf.hpp>
#include <boost/shared_ptr.hpp>
#include "orbitals.h"

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
  boost::shared_ptr<CTF::World> world(new CTF::World);
  boost::shared_ptr<psi::Wavefunction> wfn = psi::Process::environment.wavefunction();
  plugin::Orbitals orbitals(world, wfn);
  /* END SAMPLE */

  return psi::Success;
}

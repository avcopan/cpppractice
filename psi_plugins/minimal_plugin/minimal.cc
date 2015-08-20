#include <libplugin/plugin.h>
#include <liboptions/liboptions.h>
#include <libmints/mints.h>
#include <libpsio/psio.hpp>

#include <iostream>

INIT_PLUGIN

extern "C" 
int read_options(std::string name, psi::Options& options) { return false; }

extern "C" 
psi::PsiReturnType minimal(psi::Options& options)
{
  /* Your code goes here */

  std::cout << "Hello World!" << std::endl;
  psi::outfile->Printf("Hello World!\n");

  psi::MintsHelper mints;
  psi::outfile->Printf("nbf = %d\n", mints.basisset()->nbf());
  //psi::MintsHelper mints(psi::Process::environment.options, 0);

  return psi::Success;
}

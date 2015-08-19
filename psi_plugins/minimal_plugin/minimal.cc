#include <libplugin/plugin.h>
//#include <psi4-dec.h>
#include <libparallel/parallel.h>
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

  return psi::Success;
}

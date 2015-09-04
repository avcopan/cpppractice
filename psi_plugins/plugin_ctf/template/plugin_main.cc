#include <libplugin/plugin.h>
#include <liboptions/liboptions.h>
#include <libpsio/psio.hpp>

#include <ctf.hpp>

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

  enum SYM : int { NS, SY, AS, SH };

  {CTF::World world;
    CTF::Scalar<> scalar(world);
    CTF::Vector<> vector(3, world);
    CTF::Matrix<> matrix(3, 3, SYM::NS, world);
    CTF::Matrix<> symmat(3, 3, SYM::SY, world);
    int dim1[] = {3,3,3};
    int sym1[] = {SYM::NS, SYM::NS, SYM::NS};
    CTF::Tensor<> tensor(3, dim1, sym1, world);
    int dim2[] = {3,3,3,3};
    int sym2[] = {SYM::AS, SYM::NS, SYM::AS, SYM::NS};
    CTF::Tensor<> asmten(4, dim2, sym2, world);

    tensor = 0.5;
    tensor["pqrs"] = tensor["pqtu"] * tensor["turs"];

    asmten = 0.5;
    asmten["pqrs"] = asmten["pqtu"] * asmten["turs"];

    scalar.print(stdout);
    vector.print(stdout);
    matrix.print(stdout);
    symmat.print(stdout);
    tensor.print(stdout);
    asmten.print(stdout);
  }

  return psi::Success;
}

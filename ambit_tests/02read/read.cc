#include <ambit/print.h>  // ambit::print
#include <ambit/tensor.h> // abmit::initialize, ambit::finalize
#include <ambit/io/io.h>  // ambit::io::File

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // read job info from Psi files
  ambit::io::File chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  double Enuc; chkpt.read("::Nuclear rep. energy", &Enuc, 1);
  ambit::print("Nuclear repulsion energy read from CHKPT file: %20.15f\n", Enuc);

  ambit::finalize();
}

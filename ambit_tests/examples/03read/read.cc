#include <ambit/print.h>  // ambit::print
#include <ambit/tensor.h> // abmit::initialize, ambit::finalize
#include <ambit/io/io.h>  // ambit::io::File

int main(int argc, char* argv[])
{
  ambit::initialize(argc, argv);

  // declare file to be read from
  ambit::io::File chkpt("jobdata/psi.file.32", ambit::io::kOpenModeOpenExisting);
  // declare variable that will store the nuclear repulsion energy
  double Enuc;
  // Read the value in the file chkpt immediatly following "::Nuclear rep. energy" and store
  // it in the variable Enuc
  chkpt.read("::Nuclear rep. energy", &Enuc, 1);
  // Now, print the current value of Enuc
  ambit::print("Nuclear repulsion energy read from CHKPT file: %20.15f\n", Enuc);

  ambit::finalize();
}

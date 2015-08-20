#include <ctf.hpp>

int main(int argc, char** argv)
{
  int rank, np;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  enum SYM : int { NS, SY, AS, SH };

  {CTF::World world(argc, argv);
    CTF::Scalar<> scalar(1.0, world);
    CTF::Matrix<> matrix(10, 10, SYM::SY, world);
  }
  
}

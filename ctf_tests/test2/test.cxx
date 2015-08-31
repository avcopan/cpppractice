#include <ctf.hpp>

int main(int argc, char** argv)
{
  int rank, np;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  enum SYM : int { NS, SY, AS, SH };

  {CTF::World world(argc, argv);
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
    scalar.print(stdout);
    vector.print(stdout);
    matrix.print(stdout);
    symmat.print(stdout);
    tensor.print(stdout);
    asmten.print(stdout);
  }
  
}

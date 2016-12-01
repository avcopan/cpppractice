#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
  int myid, numprocs;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  std::cout << "Hello World! From " << myid << std::endl;

  MPI_Finalize();
}

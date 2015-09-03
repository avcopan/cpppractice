#include <mpi.h>
#include <cstdio>

int main(int argc, char** argv)
{
  // initialize the MPI environment
  MPI_Init(&argc, &argv);

  // get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // get the rank of the processes
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // Print Hello World message
  printf("Hello World! From processor %s, rank %d out of %d processors.\n", processor_name, world_rank, world_size);

  // Finalize the MPI environment
  MPI_Finalize();
}

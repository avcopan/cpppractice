#include <ctf.hpp>
#include <vector>

int main()
{
  int argc; char** argv;
  MPI_Init(&argc, &argv);

  enum SYM : int { NS, SY, AS, SH };

  CTF::World world(argc, argv);
  int dim1[] = {3,3,3};
  int sym1[] = {SYM::NS, SYM::NS, SYM::NS};
  CTF::Tensor<> tensor(3, dim1, sym1, world);

  tensor = 1.0;

  std::vector<int64_t> indices;
  std::vector<double>  values;
  indices.push_back(0);
  values.push_back(0.0);

  tensor[indices] = values;

  tensor.print(stdout);

  MPI_Finalize();  
}

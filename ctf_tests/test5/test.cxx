#include <ctf.hpp>
#include <vector>

int main()
{
  int argc; char** argv;
  MPI_Init(&argc, &argv);

  enum SYM : int { NS, SY, AS, SH };

  CTF::World world(argc, argv);
  int dim[] = {3,3};
  int sym[] = {SYM::SY, SYM::NS};
  CTF::Tensor<> tensor(2, dim, sym, world);

  std::vector<int64_t> indices;
  std::vector<double>  values;

  int64_t i = 2;
  int64_t j = 0;
  indices.push_back(i + 3*j);
  values.push_back(1.0);

  tensor[indices] = values;

  tensor.print(stdout);

  MPI_Finalize();  
}

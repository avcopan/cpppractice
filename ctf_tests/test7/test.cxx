#include <ctf.hpp>
#include <vector>

int main()
{
  int argc; char** argv;
  MPI_Init(&argc, &argv);

  enum SYM : int { NS, SY, AS, SH };

  CTF::World world(argc, argv);
  int dim[] = {3,3};
  int sym[] = {SYM::NS, SYM::NS};
  CTF::Tensor<> tensor(2, dim, sym, world);

  std::vector<int64_t> indices;
  std::vector<double>  values;

  for(int64_t i = 0; i < 3; ++i)
    for(int64_t j = i; j < 3; ++j)
    {
      indices.push_back(i + 3*j);
      values.push_back(1.0);
    }

  tensor[indices] = values;

  tensor["ij"] = tensor["ij"] + tensor["ji"];

  tensor.print(stdout);

  MPI_Finalize();  
}

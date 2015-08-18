#include <vector>
#include <iostream>

template<class Cl>
void print_row(const std::vector<Cl>& row)
{
  for(auto i = row.begin(); i != row.end(); ++i) // auto requires C++11
  {
    std::cout.width(3);
    std::cout << *i;
  }
}

template<class Cl>
void print_mat(const std::vector< std::vector<Cl> >& mat)
{
  std::cout << "[";
  for(auto i = mat.begin(); i != mat.end(); ++i)
  {
    if(i != mat.begin()) std::cout << " ";
    print_row(*i);
    if(i != mat.end()-1) std::cout << std::endl;
  }
  std::cout << "]" << std::endl;
}

int main()
{
  std::vector<char> v(20, 'a'); // create std vector of 20 chars and initialize all with the value 'a'
  print_row(v); std::cout << std::endl;

  // create a 20 x 15 matrix:
  // make a std vector of 20 standard vectors, each initialized to be a standard vector of size 15
  std::vector< std::vector<int> > M(20, std::vector<int>(15)); // be sure to put spaces between >s
  print_mat(M);
}

#include <cblas.h>
#include <iostream>
#include <iomanip>

/*
    C = A * B
*/
void mul(const int rowdim, const int coldim, const int sumdim,
         const double *A, const int strideA, const double *B, const int strideB, double *C, const int strideC)
{
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
              rowdim, coldim, sumdim, 1.0,
              A, strideA, B, strideB, 0.0, C, strideC);
}

void print(const int rowdim, const int coldim, const double *A)
{
  for(int i=0; i<rowdim; ++i) {
    for(int j=0; j<coldim; ++j)
      std::cout << ' ' << std::setw(3) << A[i*coldim+j];
    std::cout << std::endl;
  }
  std::cout << std::endl;
}


int main()
{
  int rowdim = 3, coldim = 4, sumdim = 5;
  double *A, *B, *C;
  A = new double[rowdim*sumdim]; int strideA = sumdim;
  B = new double[sumdim*coldim]; int strideB = coldim;
  C = new double[rowdim*coldim]; int strideC = coldim;

  for(int ij=0; ij<rowdim*sumdim; ++ij) A[ij] = ij;
  for(int ij=0; ij<sumdim*coldim; ++ij) B[ij] = ij;

  mul(rowdim, coldim, sumdim, A, strideA, B, strideB, C, strideC);

  print(rowdim, sumdim, A);
  print(sumdim, coldim, B);
  print(rowdim, coldim, C);
}

#include <iostream>
#include <omp.h>

int main() {
  #pragma omp parallel num_threads(4)

  {
    #pragma omp critical // allow one thread at a time to access below statement
    std::cout << "Hello World!  Thread Id in OpenMP stage 1 = " << omp_get_thread_num() << std::endl;
  }

  std::cout << "I am all alone" << std::endl;

  #pragma omp parallel num_threads(2)
  {
    std::cout << "Thread Id in OpenMP stage 2 = " << omp_get_thread_num() << std::endl;
  }
}

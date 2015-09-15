#include <blitz/array.h>
#include <iostream>

int main()
{
    blitz::Array<float,2> M(4,4);

    std::cout << M << std::endl;

    M(0,0) = 0.0;
    M(1,1) = 1.0;
    M(2,2) = 4.0;
    M(3,3) = 9.0;

    std::cout << M << std::endl;

}


#include <blitz/array.h>
#include <iostream>

int main()
{

    blitz::Range r(1,4);
    blitz::Array<float,2> A(r,r), B(r,r);

    blitz::firstIndex i;    // Placeholder for the first index
    blitz::secondIndex j;   // Placeholder for the second index

    A = 1.0 / (i+j-1);

    std::cout << "A = " << A << std::endl;

    B = (i == (5-j));         // Using an equation -- a bit cryptic

    std::cout << "B = " << B << std::endl;

    B = 0, 0, 0, 1,           // Using an initializer list
        0, 0, 1, 0,           
        0, 1, 0, 0,
        1, 0, 0, 0;

    std::cout << "B = " << B << std::endl;

    // Now some examples of tensor-like notation.

    blitz::Array<float,3> C(r,r,r);  // A three-dimensional array: 1..4, 1..4, 1..4

    blitz::thirdIndex k;             // Placeholder for the third index

    C = A(i,k) * B(k,j); // NOTE: this implements c_ijk = a_ik b_kj (no contraction)

    blitz::Array<float,2> D(r,r);
    D = blitz::sum(A(i,k) * B(k,j), k); // contraction d_ij = sum_k a_ik b_kj

    std::cout << "D = " << D << std::endl;

    blitz::Array<float,4> E(r,r,r,r);    // A four-dimensional array
    blitz::fourthIndex l;                // Placeholder for the fourth index

    E = A(l,j) * B(k,i);
}


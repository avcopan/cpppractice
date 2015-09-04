#include <blitz/array.h>
#include <iostream>

int main()
{

    blitz::Range r(1,4);
    blitz::Array<float,2> A(r,r), B(r,r);

    // The first will be a Hilbert matrix:
    //
    // a   =   1
    //  ij   -----
    //       i+j-1
    //
    // Blitz++ provides a set of types { blitz::firstIndex, blitz::secondIndex, ... }
    // which act as placeholders for indices.  These can be used directly
    // in expressions.  For example, we can fill out the A matrix like this:

    blitz::firstIndex i;    // Placeholder for the first index
    blitz::secondIndex j;   // Placeholder for the second index

    A = 1.0 / (i+j-1);

    std::cout << "A = " << A << std::endl;

    // A = 4 x 4
    //         1       0.5  0.333333      0.25
    //       0.5  0.333333      0.25       0.2
    //  0.333333      0.25       0.2  0.166667
    //      0.25       0.2  0.166667  0.142857

    // Now the A matrix has each element equal to a_ij = 1/(i+j-1).

    // The matrix B will be the permutation matrix
    //
    // [ 0 0 0 1 ]
    // [ 0 0 1 0 ]
    // [ 0 1 0 0 ]
    // [ 1 0 0 0 ]
    //
    // Here are two ways of filling out B:

    B = (i == (5-j));         // Using an equation -- a bit cryptic

    std::cout << "B = " << B << std::endl;

    // B = 4 x 4
    //         0         0         0         1
    //         0         0         1         0
    //         0         1         0         0
    //         1         0         0         0

    B = 0, 0, 0, 1,           // Using an initializer list
        0, 0, 1, 0,           
        0, 1, 0, 0,
        1, 0, 0, 0;

    std::cout << "B = " << B << std::endl;

    // Now some examples of tensor-like notation.

    blitz::Array<float,3> C(r,r,r);  // A three-dimensional array: 1..4, 1..4, 1..4

    blitz::thirdIndex k;             // Placeholder for the third index

    // This expression will set
    //
    // c    = a   * b
    //  ijk    ik    kj

    C = A(i,k) * B(k,j);

    // In real tensor notation, the repeated k index would imply a
    // contraction (or blitz::summation) along k.  In Blitz++, you must explicitly
    // indicate contractions using the blitz::sum(expr, index) function:

    blitz::Array<float,2> D(r,r);
    D = blitz::sum(A(i,k) * B(k,j), k);

    // The above expression computes the matrix product of A and B.

    std::cout << "D = " << D << std::endl;

    // D = 4 x 4
    //      0.25  0.333333       0.5         1
    //       0.2      0.25  0.333333       0.5
    //  0.166667       0.2      0.25  0.333333
    //  0.142857  0.166667       0.2      0.25

    // Indices like i,j,k can be used in any order in an expression.
    // For example, the following computes a kronecker product of A and B,
    // but permutes the indices along the way:

    blitz::Array<float,4> E(r,r,r,r);    // A four-dimensional array
    blitz::fourthIndex l;                // Placeholder for the fourth index

    E = A(l,j) * B(k,i);
}


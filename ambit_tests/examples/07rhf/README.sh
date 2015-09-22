# rhf.cc
# Read integrals from Psi files 35 and 33 and then compute the RHF energy and MO coefficients

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c rhf.cc

# link
c++ -std=c++11 rhf.o -o rhf.bin $LD_LIBRARY_PATH/libambit.so

# run
./rhf.bin

# clean up
rm rhf.o


# rmp2.cc
# After constructing and running RHF class, uses MO coefficients, orbital energies, and
# two-electron integrals to compute MP2 energy.

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c rmp2.cc rhf.cc

# link
c++ -std=c++11 rmp2.o rhf.o -o rmp2.bin $LD_LIBRARY_PATH/libambit.so

# run
./rmp2.bin

# clean up
rm rmp2.o rhf.o


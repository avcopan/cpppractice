# oei.cc
# Read one-electron integrals from Psi file 35

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c oei.cc

# link
c++ -std=c++11 oei.o -o oei.bin $LD_LIBRARY_PATH/libambit.so

# run
./oei.bin

# clean up
rm oei.o


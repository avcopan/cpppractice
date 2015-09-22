# read.cc
# Illustrating how to read variables from Psi4 binary files (in jobdata/)

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c read.cc

# link
c++ -std=c++11 read.o -o read.bin $LD_LIBRARY_PATH/libambit.so

# run
./read.bin

# clean up
rm read.o


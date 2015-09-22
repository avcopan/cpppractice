# main.cc
# Calls RHF class (declared in rhf.h, defined in rhf.cc), runs it, and prints MOs
# from it.

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c main.cc rhf.cc

# link
c++ -std=c++11 main.o rhf.o -o main.bin $LD_LIBRARY_PATH/libambit.so

# run
./main.bin

# clean up
rm main.o rhf.o


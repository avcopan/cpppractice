# integral.cc
# Shows how to read overlap integrals from Psi file 35 and store them in an ambit::Tensor

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c integral.cc

# link
c++ -std=c++11 integral.o -o integral.bin $LD_LIBRARY_PATH/libambit.so

# run
./integral.bin

# clean up
rm integral.o


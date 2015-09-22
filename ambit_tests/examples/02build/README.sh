# build.cc
# Illustrates how to declare and build tensors in ambit

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c build.cc

# link
c++ -std=c++11 build.o -o build.bin $LD_LIBRARY_PATH/libambit.so

# run
./build.bin

# clean up
rm build.o


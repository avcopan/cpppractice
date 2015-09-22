# helloworld.cc
# Hello World! program using Ambit's print function

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c helloworld.cc

# link
c++ -std=c++11 helloworld.o -o helloworld.bin $LD_LIBRARY_PATH/libambit.so

# run
./helloworld.bin

# clean up
rm helloworld.o


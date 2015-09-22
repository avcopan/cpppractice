# tei.cc
# Read two-electron integrals from Psi file 33

# alter these paths to fit your system
export AMBIT=/home/avcopan/Documents/code/github/ambit # = path to ambit
export LD_LIBRARY_PATH=$AMBIT/obj/src                  # = path to directory containing libambit.so

# compile
c++ -std=c++11 -I$AMBIT/include -c tei.cc

# link
c++ -std=c++11 tei.o -o tei.bin $LD_LIBRARY_PATH/libambit.so

# run
./tei.bin

# clean up
rm tei.o


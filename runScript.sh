clear
make clean
xmake project -k cmakelists
cmake -DCMAKE_BUILD_TYPE=Debug
make
xmake run

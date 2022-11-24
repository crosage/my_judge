sudo apt-get update
sudo apt install gcc g++
sudo apt install cmake

rm -rf build && mkdir build
cd build || exit
cmake ..
make
cd ..

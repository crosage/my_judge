sudo apt install libseccomp-dev libseccomp2 seccomp
rm -rf build && mkdir build
cd build || exit
cmake ..
make
cd ..

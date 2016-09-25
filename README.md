# checksum
A simple portable checksum utility

## requirements
a C++11 compliant compiler like `clang` or `gcc`
zlib - on Debian: `sudo apt-get install zlib1g-dev

## building
```sh
c++ -Wall -std=c++11 -O3 -o checksum checksum.cpp -lz
```

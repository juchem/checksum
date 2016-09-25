# checksum
A simple portable checksum utility

## requirements
- a C++11 compliant compiler like `clang` or `gcc`
- zlib

On Debian:
```sh
sudo apt-get install clang zlib1g-dev
```
or
```sh
sudo apt-get install g++ zlib1g-dev
```

## building
```sh
c++ -Wall -std=c++11 -O3 -o checksum checksum.cpp -lz
```

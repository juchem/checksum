#include <zlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <array>
#include <iostream>

int main(int argc, char **argv) {
  if (argc > 1) {
    std::cerr << "crc32    adler32  filename\n";
  } else {
    auto cmd = argv[0];
    for (auto p = cmd; *p; ++p) {
      if (*p == '/') {
        cmd = p + 1;
      }
    }
    std::cout << "usage: " << cmd << " file1 [file2 [... [fileN]]]\n";
    return EXIT_FAILURE;
  }

  auto exit = EXIT_SUCCESS;

  for (int i = 1; i < argc; ++i) {
    int fd = ::open(argv[i], O_RDONLY);
    if (fd == -1) {
      std::cout << "can't open " << argv[i] << '\n';
      exit = EXIT_FAILURE;
      continue;
    }

    std::array<unsigned char, 1u << 16> buffer;
    uLong adler = ::adler32(0L, Z_NULL, 0);
    uLong crc = ::crc32(0L, Z_NULL, 0);
    ssize_t size = 0;
    while ((size = ::read(fd, buffer.data(), buffer.size())) > 0) {
      crc = ::crc32(crc, buffer.data(), size);
      adler = ::adler32(adler, buffer.data(), size);
    }
    if (size < 0) {
      std::cout << "error reading " << argv[i] << '\n';
      exit = EXIT_FAILURE;
    } else {
      std::cout << std::hex << crc << ' ' << adler << ' ' << argv[i] << '\n';
    }

    ::close(fd);
  }

  return exit;
}

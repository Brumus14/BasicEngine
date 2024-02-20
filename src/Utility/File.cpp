#include "File.hpp"

namespace Utility {
  std::string ReadFile(std::string path, bool binary) {
    std::ifstream fileStream(path, std::ios::in | (binary ? std::ios::binary : 0)); //ERROR

    fileStream.seekg(0, std::ios::end);
    std::streampos fileSize = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);

    char * fileData = new char[fileSize];
  }
}

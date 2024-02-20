#include "File.hpp"

#include <sstream>

namespace Utility {
  //TODO More efficient algorithm and fix
  std::string ReadFile(std::string path) {
    std::ifstream fileStream(path, std::ios::in);

    std::ostringstream fileBuffer;
    fileBuffer << fileStream.rdbuf();

    fileStream.close();

    return fileBuffer.str();
  }
}

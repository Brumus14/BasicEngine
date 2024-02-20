#pragma once

#include <string>
#include <fstream>

namespace Utility {
  std::string ReadFile(std::string path, bool binary = false);
}

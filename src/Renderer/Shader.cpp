#include "Shader.hpp"

#include "Utility/File.hpp"
#include <iostream>

Shader::Shader(std::string path) {
  LoadShaderFromFile(path);
}

//TODO use shader class destroy functions instead?
Shader::~Shader() {
  if (bgfx::isValid(handle)) {
    bgfx::destroy(handle);
  }
}

bgfx::ShaderHandle Shader::GetHandle() { return handle; }

//TODO could break if file data reference is removed
//TODO const string ref parameter
//TODO use a read file function instead of directly reading
void Shader::LoadShaderFromFile(std::string path) {
  std::ifstream fileStream(path, std::ios::binary);

  fileStream.seekg(0, std::ios::end);
  std::streampos fileSize = fileStream.tellg();
  fileStream.seekg(0, std::ios::beg);

  char * fileData = new char[fileSize];
  fileStream.read(fileData, fileSize);

  fileStream.close();

  handle = bgfx::createShader(bgfx::makeRef(fileData, fileSize));
}

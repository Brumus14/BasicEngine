#pragma once

#include <bgfx/bgfx.h>
#include <string>

class Shader {
public:
  Shader(std::string path);
  ~Shader();

  bgfx::ShaderHandle GetHandle();

private:
  bgfx::ShaderHandle handle;

  void LoadShaderFromFile(std::string path);
};

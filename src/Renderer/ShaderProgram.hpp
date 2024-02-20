#pragma once

#include "Shader.hpp"

class ShaderProgram {
public:
  //TODO support compute shaders
  ShaderProgram(Shader * vertex, Shader * fragment);
  ~ShaderProgram();

  bgfx::ProgramHandle GetHandle();

private:
  bgfx::ProgramHandle handle;

  void Create(Shader * vertex, Shader * fragment);
};

#include "ShaderProgram.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(Shader * vertex, Shader * fragment) {
  Create(vertex, fragment);
}

ShaderProgram::~ShaderProgram() {
  if (bgfx::isValid(handle)) {
    bgfx::destroy(handle);
  }
}

bgfx::ProgramHandle ShaderProgram::GetHandle() { return handle; }

void ShaderProgram::Create(Shader * vertex, Shader * fragment) {
  handle = bgfx::createProgram(vertex->GetHandle(), fragment->GetHandle());
}
